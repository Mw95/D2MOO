#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2DataTbls.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>

DYNAMIC_ARRAY_TYPE(char)


BEGIN_VISIT(D2BinFieldStrc)
	FIELD(nFieldType)
	FIELD(nFieldLength)
	FIELD(nFieldOffset)
END_VISIT()


TEST_SUITE("D2DataTblsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD494D0" * doctest::skip("Needs D2Lang to work"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetStringIdFromReferenceString, dll_base + 0x000094D0);
		
		SUBCASE("")
		{
			// Input data
			char moo_szReference[64]{};
			char original_szReference[64]{};

			const auto setup_data = [](
				char(&szReference)[64]
			) {
				strcpy_s(szReference, "Amazon");
			};

			setup_data(moo_szReference);
			setup_data(original_szReference);

			// Call both implementations
			const auto moo_result = sut(moo_szReference);
			const auto original_result = original(original_szReference);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_szReference, original_szReference, "Comparing szReference");
		}
	}
	
	TEST_CASE_FIXTURE(CompCodeTxtFixture<NoopFixture>, "D2Common.0x6FD49660 (#11255)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetCodeFromCompCodeTxt, dll_base + 0x00009660);
		
		SUBCASE("")
		{
			for (auto i = 0; i < compcode_record_count; ++i)
			{
				int nCompCode = i;

				// Call both implementations
				const auto moo_result = sut(nCompCode);
				const auto original_result = original(nCompCode);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ExperienceTxtFixture<NoopFixture>, "D2Common.0x6FD49680 (#11249)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetExpRatio, dll_base + 0x00009680);
		
		SUBCASE("")
		{
			for (auto i = 0; i < experience_record_count - 1; ++i)
			{
				int nLevel = i;

				// Call both implementations
				const auto moo_result = sut(nLevel);
				const auto original_result = original(nLevel);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ExperienceTxtFixture<NoopFixture>, "D2Common.0x6FD496B0 (#10628)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetLevelThreshold, dll_base + 0x000096B0);
		
		SUBCASE("")
		{
			for (auto j = 0; j < NUMBER_OF_PLAYERCLASSES; ++j)
			{
				for (auto i = 0; i < experience_record_count - 1; ++i)
				{
					int nClass = j;
					uint32_t dwLevel = i;

					// Call both implementations
					const auto moo_result = sut(nClass, dwLevel);
					const auto original_result = original(nClass, dwLevel);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ExperienceTxtFixture<NoopFixture>, "D2Common.0x6FD496E0 (#10629)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetMaxLevel, dll_base + 0x000096E0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				int nClass = i;

				// Call both implementations
				const auto moo_result = sut(nClass);
				const auto original_result = original(nClass);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD49710 (#10630)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetCurrentLevelFromExp, dll_base + 0x00009710);
		
		REPEAT_10();

		SUBCASE("")
		{
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				int nClass = i;
				uint32_t dwExperience = random_unsigned_integer(1, 3837739017);

				// Call both implementations
				const auto moo_result = sut(nClass, dwExperience);
				const auto original_result = original(nClass, dwExperience);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD49760" * doctest::skip("Needs MPQ archives to read from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetBinFileHandle, dll_base + 0x00009760);
		
		SUBCASE("")
		{
			// The original reads bCompileTxt from its own data tables pointer
			const auto original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(dll_base + 0x00096A20);
			*original_sgptDataTables = sgptDataTables;

			// Input data
			void* moo_ppFileHandle{};
			int moo_pSize{};
			int moo_pSizeEx{};
			void* original_ppFileHandle{};
			int original_pSize{};
			int original_pSizeEx{};
			HD2ARCHIVE hArchive{};
			const char* szFile = "States";

			// Call both implementations
			sut(hArchive, szFile, &moo_ppFileHandle, &moo_pSize, &moo_pSizeEx);
			original(hArchive, szFile, &original_ppFileHandle, &original_pSize, &original_pSizeEx);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
			MOO_CHECK_EQ(moo_pSizeEx, original_pSizeEx, "Comparing pSizeEx");
			REQUIRE(moo_ppFileHandle != nullptr);
			REQUIRE(original_ppFileHandle != nullptr);
			MOO_CHECK_EQ((DynamicArray<char>{ static_cast<char*>(moo_ppFileHandle), moo_pSize }), (DynamicArray<char>{ static_cast<char*>(original_ppFileHandle), original_pSize }), "Comparing ppFileHandle");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD49850")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_AppendMemoryBuffer, dll_base + 0x00009850);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto capacity = 64;
			const auto used_size = 16;
			const auto buffer_size = 32;

			const auto codes = std::make_unique<char[]>(capacity);
			const auto buffer = std::make_unique<char[]>(buffer_size);

			for (auto i = 0; i < capacity; ++i)
			{
				codes[i] = static_cast<char>(random_unsigned_integer(0, 255));
			}

			for (auto i = 0; i < buffer_size; ++i)
			{
				buffer[i] = static_cast<char>(random_unsigned_integer(0, 255));
			}

			const auto moo_codes = std::make_unique<char[]>(capacity);
			char* moo_ppCodes = moo_codes.get();
			int moo_pSize{};
			int moo_pSizeEx{};
			const auto moo_buffer = std::make_unique<char[]>(buffer_size);
			const auto original_codes = std::make_unique<char[]>(capacity);
			char* original_ppCodes = original_codes.get();
			int original_pSize{};
			int original_pSizeEx{};
			const auto original_buffer = std::make_unique<char[]>(buffer_size);
			int nBufferSize = buffer_size;

			const auto setup_data = [&codes, &buffer, capacity, used_size, buffer_size](
				char*& ppCodes,
				int& pSize,
				int& pSizeEx,
				const std::unique_ptr<char[]>& pBuffer
			) {
				std::memcpy(ppCodes, codes.get(), capacity);
				pSize = used_size;
				pSizeEx = capacity;
				std::memcpy(pBuffer.get(), buffer.get(), buffer_size);
			};

			setup_data(moo_ppCodes, moo_pSize, moo_pSizeEx, moo_buffer);
			setup_data(original_ppCodes, original_pSize, original_pSizeEx, original_buffer);

			// Call both implementations
			const auto moo_result = sut(&moo_ppCodes, &moo_pSize, &moo_pSizeEx, moo_buffer.get(), nBufferSize);
			const auto original_result = original(&original_ppCodes, &original_pSize, &original_pSizeEx, original_buffer.get(), nBufferSize);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ((DynamicArray<char>{ moo_ppCodes, capacity }), (DynamicArray<char>{ original_ppCodes, capacity }), "Comparing ppCodes");
			MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
			MOO_CHECK_EQ(moo_pSizeEx, original_pSizeEx, "Comparing pSizeEx");
			MOO_CHECK_EQ((DynamicArray<char>{ moo_buffer.get(), buffer_size }), (DynamicArray<char>{ original_buffer.get(), buffer_size }), "Comparing pBuffer");

			// Check specific values
			CHECK_EQ(moo_result, used_size);
			CHECK_EQ(moo_ppCodes, moo_codes.get());
			CHECK_EQ(moo_pSize, used_size + buffer_size);
		}

		// NOTE: Reallocation is not (yet) tested because the tests don't use Fog.dll for allocations
	}
	
	TEST_CASE_FIXTURE(CharStatsTxtFixture<NoopFixture>, "D2Common.0x6FD4E4B0 (#10593)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetCharstatsTxtTable, dll_base + 0x0000E4B0);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4E4C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetAnimData, dll_base + 0x0000E4C0);
		
		SUBCASE("")
		{
			// The original reads pAnimData from its own data tables pointer
			const auto original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(dll_base + 0x00096A20);
			*original_sgptDataTables = sgptDataTables;

			// Global data
			D2AnimDataTableStrc anim_data{};
			anim_data.tDefaultRecord.dwFrames = 10;
			anim_data.tDefaultRecord.dwAnimSpeed = 256;

			D2AnimDataTableStrc* const previous_anim_data = sgptDataTables->pAnimData;
			sgptDataTables->pAnimData = &anim_data;

			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			sgptDataTables->pAnimData = previous_anim_data;

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			CHECK_EQ(moo_result, &anim_data);
			CHECK_EQ(original_result, &anim_data);
		}
	}
	
	TEST_CASE_FIXTURE(DifficultyLevelsTxtFixture<NoopFixture>, "D2Common.0x6FD4E4D0 (#10655)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetDifficultyLevelsTxtRecord, dll_base + 0x0000E4D0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 3; ++i)
			{
				int nDifficulty = i;

				// Call both implementations
				const auto moo_result = sut(nDifficulty);
				const auto original_result = original(nDifficulty);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4E500" * doctest::skip("Needs MPQ archives to load the txt files from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadStatesTxt, dll_base + 0x0000E500);
		
		SUBCASE("")
		{
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4F4A0" * doctest::skip("Frees the loaded tables, which needs them to be allocated by Fog.dll"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_UnloadStatesTxt, dll_base + 0x0000F4A0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4F5A0" * doctest::skip("Needs MPQ archives to load the txt files from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadPetTypeTxt, dll_base + 0x0000F5A0);
		
		SUBCASE("")
		{
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<MissilesTxtFixture<ObjectsTxtFixture<MonStatsTxtFixture<CharStatsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FD4F990 (#11298)" * doctest::skip("Needs D2Lang to work for monsters and items"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetUnitNameFromUnit, dll_base + 0x0000F990);
		
		SUBCASE("UNIT_PLAYER")
		{
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				char moo_szName[64]{};
				D2UnitStrc original_pUnit{};
				char original_szName[64]{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit,
					char(&szName)[64]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_szName);
				setup_data(original_pUnit, original_szName);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, moo_szName);
				const auto original_result = original(&original_pUnit, original_szName);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
			}
		}

		SUBCASE("UNIT_MONSTER")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				char moo_szName[64]{};
				D2UnitStrc original_pUnit{};
				char original_szName[64]{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit,
					char(&szName)[64]
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_szName);
				setup_data(original_pUnit, original_szName);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, moo_szName);
				const auto original_result = original(&original_pUnit, original_szName);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
			}
		}

		SUBCASE("UNIT_OBJECT")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				char moo_szName[64]{};
				D2UnitStrc original_pUnit{};
				char original_szName[64]{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit,
					char(&szName)[64]
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_szName);
				setup_data(original_pUnit, original_szName);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, moo_szName);
				const auto original_result = original(&original_pUnit, original_szName);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
			}
		}

		SUBCASE("UNIT_MISSILE")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				char moo_szName[64]{};
				D2UnitStrc original_pUnit{};
				char original_szName[64]{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit,
					char(&szName)[64]
				) {
					pUnit.dwUnitType = UNIT_MISSILE;
					pUnit.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_szName);
				setup_data(original_pUnit, original_szName);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, moo_szName);
				const auto original_result = original(&original_pUnit, original_szName);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
			}
		}

		SUBCASE("UNIT_ITEM")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				char moo_szName[64]{};
				D2UnitStrc original_pUnit{};
				char original_szName[64]{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit,
					char(&szName)[64]
				) {
					pUnit.dwUnitType = UNIT_ITEM;
					pUnit.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_szName);
				setup_data(original_pUnit, original_szName);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, moo_szName);
				const auto original_result = original(&original_pUnit, original_szName);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
			}
		}

		SUBCASE("UNIT_TILE")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			char moo_szName[64]{};
			D2UnitStrc original_pUnit{};
			char original_szName[64]{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				char(&szName)[64]
			) {
				pUnit.dwUnitType = UNIT_TILE;
			};

			setup_data(moo_pUnit, moo_szName);
			setup_data(original_pUnit, original_szName);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, moo_szName);
			const auto original_result = original(&original_pUnit, original_szName);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
		}

		SUBCASE("pUnit == nullptr")
		{
			// Input data
			char moo_szName[64]{};
			char original_szName[64]{};

			// Call both implementations
			const auto moo_result = sut(nullptr, moo_szName);
			const auto original_result = original(nullptr, original_szName);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<MissilesTxtFixture<ObjectsTxtFixture<MonStatsTxtFixture<CharStatsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FD4FB50 (#11299)" * doctest::skip("Needs D2Lang to work for monsters and items"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetUnitNameFromUnitTypeAndClassId, dll_base + 0x0000FB50);
		
		SUBCASE("UNIT_PLAYER")
		{
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				// Input data
				char moo_szName[64]{};
				char original_szName[64]{};
				int nUnitType = UNIT_PLAYER;
				int nClassId{};

				// Call both implementations
				const auto moo_result = sut(nUnitType, nClassId, moo_szName);
				const auto original_result = original(nUnitType, nClassId, original_szName);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
			}
		}

		SUBCASE("UNIT_MONSTER")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				char moo_szName[64]{};
				char original_szName[64]{};
				int nUnitType = UNIT_MONSTER;
				int nClassId = i;

				// Call both implementations
				const auto moo_result = sut(nUnitType, nClassId, moo_szName);
				const auto original_result = original(nUnitType, nClassId, original_szName);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
			}
		}

		SUBCASE("UNIT_OBJECT")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				char moo_szName[64]{};
				char original_szName[64]{};
				int nUnitType = UNIT_OBJECT;
				int nClassId = i;

				// Call both implementations
				const auto moo_result = sut(nUnitType, nClassId, moo_szName);
				const auto original_result = original(nUnitType, nClassId, original_szName);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
			}
		}

		SUBCASE("UNIT_MISSILE")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				char moo_szName[64]{};
				char original_szName[64]{};
				int nUnitType = UNIT_MISSILE;
				int nClassId = i;

				// Call both implementations
				const auto moo_result = sut(nUnitType, nClassId, moo_szName);
				const auto original_result = original(nUnitType, nClassId, original_szName);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
			}
		}

		SUBCASE("UNIT_ITEM")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				char moo_szName[64]{};
				char original_szName[64]{};
				int nUnitType = UNIT_ITEM;
				int nClassId = i;

				// Call both implementations
				const auto moo_result = sut(nUnitType, nClassId, moo_szName);
				const auto original_result = original(nUnitType, nClassId, original_szName);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
			}
		}

		SUBCASE("UNIT_TILE")
		{
			// Input data
			char moo_szName[64]{};
			char original_szName[64]{};
			int nUnitType = UNIT_TILE;
			int nClassId = 0;

			// Call both implementations
			const auto moo_result = sut(nUnitType, nClassId, moo_szName);
			const auto original_result = original(nUnitType, nClassId, original_szName);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4FCF0 (#10580)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_WriteBinFile, dll_base + 0x0000FCF0);
		
		SUBCASE("")
		{
			// Both implementations write to DATA\GLOBAL\EXCEL relative to the working directory
			const auto file_name = "D2DataTblsTests_WriteBinFile.bin";
			const auto file_path = working_directory / "DATA" / "GLOBAL" / "EXCEL" / file_name;
			std::filesystem::create_directories(file_path.parent_path());

			const auto read_and_remove_file = [&file_path]() {
				std::vector<char> content;
				{
					std::ifstream file(file_path, std::ios::binary);
					REQUIRE(file.is_open());
					content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
				}
				std::filesystem::remove(file_path);
				return content;
			};

			// Input data
			const auto buffer_size = 32;
			const auto buffer = std::make_unique<char[]>(buffer_size);

			for (auto i = 0; i < buffer_size; ++i)
			{
				buffer[i] = static_cast<char>(random_unsigned_integer(0, 255));
			}

			char moo_szFileName[64]{};
			char original_szFileName[64]{};
			const auto moo_pWriteBuffer = std::make_unique<char[]>(buffer_size);
			const auto original_pWriteBuffer = std::make_unique<char[]>(buffer_size);
			size_t nBufferSize = buffer_size;
			int nRecordCount = 4;

			const auto setup_data = [&buffer, buffer_size, file_name](
				char(&szFileName)[64],
				const std::unique_ptr<char[]>& pWriteBuffer
			) {
				strcpy_s(szFileName, file_name);
				std::memcpy(pWriteBuffer.get(), buffer.get(), buffer_size);
			};

			setup_data(moo_szFileName, moo_pWriteBuffer);
			setup_data(original_szFileName, original_pWriteBuffer);

			// Call both implementations
			sut(moo_szFileName, moo_pWriteBuffer.get(), nBufferSize, nRecordCount);
			auto moo_file = read_and_remove_file();
			original(original_szFileName, original_pWriteBuffer.get(), nBufferSize, nRecordCount);
			auto original_file = read_and_remove_file();

			// Compare written files
			REQUIRE_EQ(moo_file.size(), sizeof(nRecordCount) + buffer_size);
			REQUIRE_EQ(moo_file.size(), original_file.size());
			const auto file_size = static_cast<int>(moo_file.size());
			MOO_CHECK_EQ((DynamicArray<char>{ moo_file.data(), file_size }), (DynamicArray<char>{ original_file.data(), file_size }), "Comparing written file");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_szFileName, original_szFileName, "Comparing szFileName");
			MOO_CHECK_EQ((DynamicArray<char>{ moo_pWriteBuffer.get(), buffer_size }), (DynamicArray<char>{ original_pWriteBuffer.get(), buffer_size }), "Comparing pWriteBuffer");

			// Check specific values
			int written_record_count{};
			std::memcpy(&written_record_count, moo_file.data(), sizeof(written_record_count));
			CHECK_EQ(written_record_count, nRecordCount);
			CHECK_EQ(std::memcmp(moo_file.data() + sizeof(nRecordCount), buffer.get(), buffer_size), 0);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD4FD70 (#10578)" * doctest::skip("Needs MPQ archives to load the txt files from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_CompileTxt, dll_base + 0x0000FD70);
		
		SUBCASE("")
		{
			// The original reads bCompileTxt from its own data tables pointer
			const auto original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(dll_base + 0x00096A20);
			*original_sgptDataTables = sgptDataTables;

			// Input data
			D2BinFieldStrc moo_pTbl{};
			int moo_pRecordCount{};
			D2BinFieldStrc original_pTbl{};
			int original_pRecordCount{};
			HD2ARCHIVE hArchive{};
			const char* szName = "PetType";
			size_t dwSize = sizeof(D2PetTypeTxt);

			const auto setup_data = [](
				D2BinFieldStrc& pTbl
			) {
				// Only the terminating entry is needed, since the field table is only used when compiling from txt
				pTbl.szFieldName = "end";
				pTbl.nFieldType = TXTFIELD_NONE;
			};

			setup_data(moo_pTbl);
			setup_data(original_pTbl);

			// Call both implementations
			const auto moo_result = static_cast<D2PetTypeTxt*>(sut(hArchive, szName, &moo_pTbl, &moo_pRecordCount, dwSize));
			const auto original_result = static_cast<D2PetTypeTxt*>(original(hArchive, szName, &original_pTbl, &original_pRecordCount, dwSize));
			
			// Compare return values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			MOO_CHECK_EQ((DynamicArray<char>{ reinterpret_cast<char*>(moo_result), static_cast<int>(dwSize) * moo_pRecordCount }), (DynamicArray<char>{ reinterpret_cast<char*>(original_result), static_cast<int>(dwSize) * original_pRecordCount }), "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTbl, original_pTbl, "Comparing pTbl");
			MOO_CHECK_EQ(moo_pRecordCount, original_pRecordCount, "Comparing pRecordCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD500F0 (#11242)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_ToggleCompileTxtFlag, dll_base + 0x000100F0);
		
		SUBCASE("")
		{
			const auto working_directory = std::filesystem::current_path();
			const auto d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

			const auto original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(d2common_base + 0x00096A20);

			for (auto silent : { 0, 1 })
			{
				BOOL bSilent = silent;

				// Call both implementations
				sut(bSilent);
				original(bSilent);

				// Compare global modified state
				MOO_CHECK_EQ(sgptDataTables, *original_sgptDataTables, "Comparing sgptDataTables")
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD50110 (#10579)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_UnloadBin, dll_base + 0x00010110);
		
		SUBCASE("pBinFile == nullptr")
		{
			void* moo_pBinFile = nullptr;
			void* original_pBinFile = nullptr;

			// Call both implementations
			sut(moo_pBinFile);
			original(original_pBinFile);
		}

		// NOTE: Freeing an actual bin file is not (yet) tested because the tests don't use Fog.dll for allocations
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD50150 (#10575)" * doctest::skip("Frees the loaded tables, which needs them to be allocated by Fog.dll"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_UnloadAllBins, dll_base + 0x00010150);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD504B0 (#10576)" * doctest::skip("Needs MPQ archives to load the txt files from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadAllTxts, dll_base + 0x000104B0);
		
		SUBCASE("")
		{
			HD2ARCHIVE hArchive{};
			int a2{};
			int a3{};

			// Call both implementations
			sut(hArchive, a2, a3);
			original(hArchive, a2, a3);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD507B0" * doctest::skip("Needs MPQ archives to load the txt files from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadSomeTxts, dll_base + 0x000107B0);
		
		SUBCASE("")
		{
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD50FB0" * doctest::skip("Needs MPQ archives to load the txt files from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadCharStatsTxt, dll_base + 0x00010FB0);
		
		SUBCASE("")
		{
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD51BF0" * doctest::skip("Needs MPQ archives to load the txt files from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadDifficultyLevelsTxt, dll_base + 0x00011BF0);
		
		SUBCASE("")
		{
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
}
