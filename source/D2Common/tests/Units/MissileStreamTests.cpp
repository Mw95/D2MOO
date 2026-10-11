#include <D2CommonTestDefines.h>

#ifdef MISSILESTREAM_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <utility>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Fog.h>

#include <D2Collision.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Path/Path.h>
#include <Units/Missile.h>
#include <Units/MissileStream.h>
#include <Units/Player.h>
#include <Units/Units.h>


DYNAMIC_ARRAY_TYPE(int)


enum class StreamType {
	New = 0,
	Small = 1,
	Large = 2
};


TEST_SUITE("MissileStreamTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	constexpr int32_t nRoomX = 200;
	constexpr int32_t nRoomY = 200;
	constexpr int32_t nRoomSize = 20;

	// Records the calls of the callbacks passed to the tested functions, so that the calls of both implementations can be compared
	std::vector<int> recorded_calls;

	void __fastcall record_hit(D2UnitStrc* pUnit, D2UnitStrc* pTargetUnit)
	{
		recorded_calls.push_back(static_cast<int>(pUnit->dwUnitId));
		recorded_calls.push_back(static_cast<int>(pTargetUnit->dwUnitId));
	}

	int __fastcall record_create(D2UnitStrc* pUnit, int nPrevious, int nX, int nY, int nValue, int nMode)
	{
		recorded_calls.insert(recorded_calls.end(), { static_cast<int>(pUnit->dwUnitId), nPrevious, nX, nY, nValue, nMode });
		// The returned value is stored in the stream and passed as nPrevious to later calls
		return static_cast<int>(recorded_calls.size());
	}

	void __fastcall record_free(int nValue)
	{
		recorded_calls.push_back(nValue);
	}

	const auto check_recorded_calls = [](std::vector<int>& moo_calls, std::vector<int>& original_calls) {
		CHECK_EQ(moo_calls.size(), original_calls.size());
		if (moo_calls.size() == original_calls.size())
		{
			DynamicArray<int> moo_recorded_calls{ moo_calls.data(), static_cast<int>(moo_calls.size()) };
			DynamicArray<int> original_recorded_calls{ original_calls.data(), static_cast<int>(original_calls.size()) };
			MOO_CHECK_EQ(moo_recorded_calls, original_recorded_calls, "Comparing recorded callback calls");
		}
	};

	// Start and target lie inside the room, but neither on a straight nor on a diagonal line,
	// so the path computed by IDA* consists of at least two points, the last one being the target
	const auto random_path_coords = []() {
		const auto start_x = nRoomX + random_unsigned_integer(2, 4);
		const auto start_y = nRoomY + random_unsigned_integer(2, 4);
		const auto delta_x = random_unsigned_integer(7, 14);
		const auto delta_y = random_unsigned_integer(1, delta_x - 1);

		return std::make_pair(
			D2PathPointStrc{ static_cast<uint16_t>(start_x), static_cast<uint16_t>(start_y) },
			D2PathPointStrc{ static_cast<uint16_t>(start_x + delta_x), static_cast<uint16_t>(start_y + delta_y) }
		);
	};

	// Sets up a room with a collision grid and a missile in it, whose dynamic path leads from tStartCoord to tTargetCoord.
	// D2Common_10142 computes the path with IDA* (PATHTYPE_MISSILE_STREAM) using the seed of the missile.
	const auto setup_missile_path = [](
		D2UnitStrc& pMissile,
		D2DynamicPathStrc& pDynamicPath,
		D2ActiveRoomStrc& pRoom,
		D2ActiveRoomStrc** pRoomList,
		D2RoomCollisionGridStrc& pCollisionGrid,
		uint16_t* pCollisionMask,
		uint32_t nUnitId,
		uint32_t nSeed,
		D2PathPointStrc tStartCoord,
		D2PathPointStrc tTargetCoord
	) {
		pRoom.tCoords.nSubtileX = nRoomX;
		pRoom.tCoords.nSubtileY = nRoomY;
		pRoom.tCoords.nSubtileWidth = nRoomSize;
		pRoom.tCoords.nSubtileHeight = nRoomSize;
		pRoom.pCollisionGrid = &pCollisionGrid;
		// The adjacent rooms list of a room contains the room itself
		pRoomList[0] = &pRoom;
		pRoom.ppRoomList = pRoomList;
		pRoom.nNumRooms = 1;

		pCollisionGrid.pRoomCoords = pRoom.tCoords;
		pCollisionGrid.pCollisionMask = pCollisionMask;

		pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tStartCoord.X);
		pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tStartCoord.Y);
		pDynamicPath.tTargetCoord = tTargetCoord;
		pDynamicPath.pRoom = &pRoom;
		pDynamicPath.pUnit = &pMissile;
		pDynamicPath.nMoveTestCollisionMask = COLLIDE_WALL;
		pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_NONE;
		pDynamicPath.nIDAStarInitFScore = 255;

		pMissile.dwUnitType = UNIT_MISSILE;
		// No missiles.txt record, so the missile has no collision footprint
		pMissile.dwClassId = -1;
		pMissile.dwUnitId = nUnitId;
		pMissile.pSeed.nLowSeed = nSeed;
		pMissile.pSeed.nHighSeed = 666;
		pMissile.pDynamicPath = &pDynamicPath;
	};

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC230 (#11213)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_AllocMissileStream, dll_base + 0x0007C230);
		const auto [moo_free, original_free] = make_function_pair(MISSTREAM_FreeMissileStream, dll_base + 0x0007C280);

		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2MissileDataStrc moo_pMissileData{};
			D2UnitStrc original_pMissile{};
			D2MissileDataStrc original_pMissileData{};

			const auto setup_data = [](
				D2UnitStrc& pMissile,
				D2MissileDataStrc& pMissileData
			) {
				pMissile.dwUnitType = UNIT_MISSILE;
				pMissile.pMissileData = &pMissileData;
			};

			setup_data(moo_pMissile, moo_pMissileData);
			setup_data(original_pMissile, original_pMissileData);

			// Call both implementations
			sut(&moo_pMissile);
			original(&original_pMissile);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");

			// Free allocated memory
			moo_free(&moo_pMissile);
			original_free(&original_pMissile);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC280 (#11214)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_FreeMissileStream, dll_base + 0x0007C280);
		const auto [moo_alloc, original_alloc] = make_function_pair(MISSTREAM_AllocMissileStream, dll_base + 0x0007C230);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2MissileDataStrc moo_pMissileData{};
			D2UnitStrc original_pMissile{};
			D2MissileDataStrc original_pMissileData{};

			const auto setup_data = [](
				D2UnitStrc& pMissile,
				D2MissileDataStrc& pMissileData
			) {
				pMissile.dwUnitType = UNIT_MISSILE;
				pMissile.pMissileData = &pMissileData;
			};

			setup_data(moo_pMissile, moo_pMissileData);
			setup_data(original_pMissile, original_pMissileData);

			moo_alloc(&moo_pMissile);
			original_alloc(&original_pMissile);

			// Call both implementations
			sut(&moo_pMissile);
			original(&original_pMissile);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC2E0 (#11215)" * doctest::skip("Setup is broken as of now"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_ExecuteHit, dll_base + 0x0007C2E0);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			const auto path_coords = random_path_coords();
			const auto tStartCoord = path_coords.first;
			const auto tTargetCoord = path_coords.second;
			const auto seed = random_unsigned_integer();
			const auto unit_id = random_unsigned_integer();
			const auto target_unit_id = random_unsigned_integer();
			// A dead target is not returned by D2Common_10407, so pfnHit is not called
			const uint32_t target_anim_mode = GENERATE(PLRMODE_NEUTRAL, PLRMODE_DEATH);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc* moo_aRoomList[1]{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_aCollisionMask[nRoomSize * nRoomSize]{};
			D2UnitStrc moo_pTargetUnit{};
			D2DynamicPathStrc moo_pTargetDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2ActiveRoomStrc* original_aRoomList[1]{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_aCollisionMask[nRoomSize * nRoomSize]{};
			D2UnitStrc original_pTargetUnit{};
			D2DynamicPathStrc original_pTargetDynamicPath{};
			int nCollisionMask = COLLIDE_MONSTER;
			int nCollisionPattern = COLLISION_UNIT_SIZE_POINT;

			const auto setup_data = [tStartCoord, tTargetCoord, seed, unit_id, target_unit_id, target_anim_mode](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom,
				D2ActiveRoomStrc** pRoomList,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t* pCollisionMask,
				D2UnitStrc& pTargetUnit,
				D2DynamicPathStrc& pTargetDynamicPath
			) {
				setup_missile_path(pUnit, pDynamicPath, pRoom, pRoomList, pCollisionGrid, pCollisionMask, unit_id, seed, tStartCoord, tTargetCoord);

				// Only the target coordinate collides with nCollisionMask, so the check fails for all other path points
				pCollisionMask[(tTargetCoord.X - nRoomX) + (tTargetCoord.Y - nRoomY) * nRoomSize] = COLLIDE_MONSTER;

				// A player standing on the target coordinate, players have a size of COLLISION_UNIT_SIZE_SMALL
				pTargetUnit.dwUnitType = UNIT_PLAYER;
				pTargetUnit.dwUnitId = target_unit_id;
				pTargetUnit.dwAnimMode = target_anim_mode;
				pTargetUnit.pDynamicPath = &pTargetDynamicPath;
				pTargetDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tTargetCoord.X);
				pTargetDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tTargetCoord.Y);
				pTargetDynamicPath.pUnit = &pTargetUnit;
				pRoom.pUnitFirst = &pTargetUnit;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom, moo_aRoomList, moo_pCollisionGrid, moo_aCollisionMask, moo_pTargetUnit, moo_pTargetDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom, original_aRoomList, original_pCollisionGrid, original_aCollisionMask, original_pTargetUnit, original_pTargetDynamicPath);

			// Call both implementations
			recorded_calls.clear();
			sut(&moo_pUnit, nCollisionMask, nCollisionPattern, record_hit);
			auto moo_calls = std::move(recorded_calls);

			recorded_calls.clear();
			original(&original_pUnit, nCollisionMask, nCollisionPattern, record_hit);
			auto original_calls = std::move(recorded_calls);

			// Compare callback calls
			check_recorded_calls(moo_calls, original_calls);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC3B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_Return1, dll_base + 0x0007C3B0);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id1 = random_unsigned_integer();
			const auto unit_id2 = random_unsigned_integer();

			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};

			const auto setup_data = [unit_id1, unit_id2](
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				pUnit1.dwUnitId = unit_id1;
				pUnit2.dwUnitId = unit_id2;
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			const auto original_result = original(&original_pUnit1, &original_pUnit2);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC3C0 (#11216)" * doctest::skip("Setup is broken as of now"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_Update, dll_base + 0x0007C3C0);

		REPEAT_10();
		
		SUBCASE("")
		{
			constexpr int large_stream_size = static_cast<int>(D2DynamicPathStrc::MAXPATHLEN) + 22;

			// Input data
			const auto stream_type = GENERATE(StreamType::New, StreamType::Small, StreamType::Large);
			const auto path_coords = random_path_coords();
			const auto tStartCoord = path_coords.first;
			const auto tTargetCoord = path_coords.second;
			const auto seed = random_unsigned_integer();
			const auto a1_unit_id = random_unsigned_integer();
			const auto missile_unit_id = random_unsigned_integer();
			const auto stream_value = static_cast<int>(random_unsigned_integer());

			D2UnitStrc moo_a1{};
			D2UnitStrc moo_pMissile{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc* moo_aRoomList[1]{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_aCollisionMask[nRoomSize * nRoomSize]{};
			D2MissileDataStrc moo_pMissileData{};
			D2MissileStreamStrc moo_pStream{};
			int32_t moo_aStream[large_stream_size]{};
			D2UnitStrc original_a1{};
			D2UnitStrc original_pMissile{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2ActiveRoomStrc* original_aRoomList[1]{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_aCollisionMask[nRoomSize * nRoomSize]{};
			D2MissileDataStrc original_pMissileData{};
			D2MissileStreamStrc original_pStream{};
			int32_t original_aStream[large_stream_size]{};
			int a4 = random_unsigned_integer(1, 1000);
			// a3 / a4 must not be 0. If it is larger than the number of path points, additional missiles are created (pfCreate with mode 2).
			// Otherwise a3 / a4 == 1, so pfCreate is only called with mode 0.
			int a3 = a4 * (stream_type == StreamType::Large ? 1 : random_unsigned_integer(static_cast<uint32_t>(D2DynamicPathStrc::MAXPATHLEN), 120)) + random_unsigned_integer(0, a4 - 1);

			const auto setup_data = [large_stream_size, stream_type, tStartCoord, tTargetCoord, seed, a1_unit_id, missile_unit_id, stream_value](
				D2UnitStrc& a1,
				D2UnitStrc& pMissile,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom,
				D2ActiveRoomStrc** pRoomList,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t* pCollisionMask,
				D2MissileDataStrc& pMissileData,
				D2MissileStreamStrc& pStream,
				int32_t* pStreamArray
			) {
				setup_missile_path(pMissile, pDynamicPath, pRoom, pRoomList, pCollisionGrid, pCollisionMask, missile_unit_id, seed, tStartCoord, tTargetCoord);

				a1.dwUnitId = a1_unit_id;

				pMissile.pMissileData = &pMissileData;
				pMissileData.pStream = &pStream;

				switch (stream_type)
				{
				case StreamType::Small:
					// Gets reallocated by the function, so it has to be allocated with the same allocator
					pStream.unk0x00 = static_cast<int32_t*>(D2_ALLOC_POOL(nullptr, sizeof(int32_t)));
					pStream.unk0x00[0] = stream_value;
					pStream.unk0x04 = 1;
					break;
				case StreamType::Large:
					for (int i = 0; i < large_stream_size; ++i)
					{
						pStreamArray[i] = stream_value + i;
					}
					pStream.unk0x00 = pStreamArray;
					pStream.unk0x04 = large_stream_size;
					break;
				default:
					break;
				}
			};

			setup_data(moo_a1, moo_pMissile, moo_pDynamicPath, moo_pRoom, moo_aRoomList, moo_pCollisionGrid, moo_aCollisionMask, moo_pMissileData, moo_pStream, moo_aStream);
			setup_data(original_a1, original_pMissile, original_pDynamicPath, original_pRoom, original_aRoomList, original_pCollisionGrid, original_aCollisionMask, original_pMissileData, original_pStream, original_aStream);

			// Call both implementations
			recorded_calls.clear();
			sut(&moo_a1, &moo_pMissile, a3, a4, record_create, record_free);
			auto moo_calls = std::move(recorded_calls);

			recorded_calls.clear();
			original(&original_a1, &original_pMissile, a3, a4, record_create, record_free);
			auto original_calls = std::move(recorded_calls);

			// Compare callback calls
			check_recorded_calls(moo_calls, original_calls);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
			MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			MOO_CHECK_EQ(moo_pStream, original_pStream, "Comparing pStream");

			// Free memory allocated by the function or the setup
			if (stream_type != StreamType::Large)
			{
				if (moo_pStream.unk0x00)
				{
					D2_FREE_POOL(nullptr, moo_pStream.unk0x00);
				}
				if (original_pStream.unk0x00)
				{
					D2_FREE_POOL(nullptr, original_pStream.unk0x00);
				}
			}
		}
	}
}

#endif
