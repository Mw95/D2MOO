#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgDrlgVer.h>
#include <Fog.h>


TEST_SUITE("D2DrlgDrlgVerTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD782A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGVER_AllocVertex, dll_base + 0x000382A0);
		
		SUBCASE("")
		{
			uint8_t nDirection = random_unsigned_integer(0, 255);

			// Call both implementations
			const auto moo_result = sut(nullptr, nDirection);
			const auto original_result = original(nullptr, nDirection);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD782D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGVER_CreateVertices, dll_base + 0x000382D0);
		
		SUBCASE("")
		{
			// Input data
			const auto nRoomDirection = GENERATE(0, 1, 2, 3);
			const auto bPreset = GENERATE(FALSE, TRUE);

			D2DrlgVertexStrc* moo_ppVertices{};
			D2DrlgCoordStrc moo_pDrlgCoord{};
			D2DrlgOrthStrc moo_pDrlgRoomData{};
			D2DrlgCoordStrc moo_pBox{};
			D2DrlgVertexStrc* original_ppVertices{};
			D2DrlgCoordStrc original_pDrlgCoord{};
			D2DrlgOrthStrc original_pDrlgRoomData{};
			D2DrlgCoordStrc original_pBox{};
			uint8_t nDirection = random_unsigned_integer(0, 255);

			const auto setup_data = [nRoomDirection, bPreset](
				D2DrlgVertexStrc*& ppVertices,
				D2DrlgCoordStrc& pDrlgCoord,
				D2DrlgOrthStrc& pDrlgRoomData,
				D2DrlgCoordStrc& pBox
			) {
				pDrlgCoord.nPosX = 10;
				pDrlgCoord.nPosY = 20;
				pDrlgCoord.nWidth = 8;
				pDrlgCoord.nHeight = 6;

				// Adjacent room box lying within the edges of pDrlgCoord, so that new vertices get inserted
				pBox.nPosX = 12;
				pBox.nPosY = 22;
				pBox.nWidth = 3;
				pBox.nHeight = 2;

				pDrlgRoomData.nDirection = nRoomDirection;
				pDrlgRoomData.bPreset = bPreset;
				pDrlgRoomData.pBox = &pBox;
			};

			setup_data(moo_ppVertices, moo_pDrlgCoord, moo_pDrlgRoomData, moo_pBox);
			setup_data(original_ppVertices, original_pDrlgCoord, original_pDrlgRoomData, original_pBox);

			// Call both implementations
			sut(nullptr, &moo_ppVertices, &moo_pDrlgCoord, nDirection, &moo_pDrlgRoomData);
			original(nullptr, &original_ppVertices, &original_pDrlgCoord, nDirection, &original_pDrlgRoomData);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_ppVertices, original_ppVertices, "Comparing ppVertices");
			MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
			MOO_CHECK_EQ(moo_pDrlgRoomData, original_pDrlgRoomData, "Comparing pDrlgRoomData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD786C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGVER_FreeVertices, dll_base + 0x000386C0);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgVertexStrc* moo_ppVertices{};
			D2DrlgVertexStrc* original_ppVertices{};

			const auto setup_data = [](
				D2DrlgVertexStrc*& ppVertices
			) {
				// The vertices get freed, so they have to be allocated from the pool (circular list of 4 vertices)
				D2DrlgVertexStrc* pPrevious = nullptr;
				for (int i = 0; i < 4; ++i)
				{
					D2DrlgVertexStrc* pVertex = D2_CALLOC_STRC_POOL(nullptr, D2DrlgVertexStrc);
					pVertex->nPosX = i;
					pVertex->nPosY = i;
					if (pPrevious)
					{
						pPrevious->pNext = pVertex;
					}
					else
					{
						ppVertices = pVertex;
					}
					pPrevious = pVertex;
				}
				pPrevious->pNext = ppVertices;
			};

			setup_data(moo_ppVertices);
			setup_data(original_ppVertices);

			// Call both implementations
			sut(nullptr, &moo_ppVertices);
			original(nullptr, &original_ppVertices);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_ppVertices, original_ppVertices, "Comparing ppVertices");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78730")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGVER_GetCoordDiff, dll_base + 0x00038730);

		SUBCASE("")
		{
			// Input data
			const auto x_offset = GENERATE(-1, 0, 1);
			const auto y_offset = GENERATE(-1, 0, 1);

			const auto x = random_unsigned_integer(0, 255);
			const auto y = random_unsigned_integer(0, 255);
			const auto next_x = x + x_offset;
			const auto next_y = y + y_offset;

			D2DrlgVertexStrc moo_pDrlgVertex{};
			D2DrlgVertexStrc moo_pNext{};
			int moo_pDiffX{};
			int moo_pDiffY{};
			D2DrlgVertexStrc original_pDrlgVertex{};
			D2DrlgVertexStrc original_pNext{};
			int original_pDiffX{};
			int original_pDiffY{};

			const auto setup_data = [x, y, next_x, next_y](
				D2DrlgVertexStrc& pDrlgVertex,
				D2DrlgVertexStrc& pNext,
				int& pDiffX,
				int& pDiffY
			) {
				pDrlgVertex.pNext = &pNext;
				pDrlgVertex.nPosX = x;
				pDrlgVertex.nPosY = y;
				pNext.nPosX = next_x;
				pNext.nPosY = next_y;
			};

			setup_data(moo_pDrlgVertex, moo_pNext, moo_pDiffX, moo_pDiffY);
			setup_data(original_pDrlgVertex, original_pNext, original_pDiffX, original_pDiffY);

			// Call both implementations
			sut(&moo_pDrlgVertex, &moo_pDiffX, &moo_pDiffY);
			original(&original_pDrlgVertex, &original_pDiffX, &original_pDiffY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgVertex, original_pDrlgVertex, "Comparing pDrlgVertex");
			MOO_CHECK_EQ(moo_pDiffX, original_pDiffX, "Comparing pDiffX");
			MOO_CHECK_EQ(moo_pDiffY, original_pDiffY, "Comparing pDiffY");
		}
	}
}
