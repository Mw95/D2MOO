# Note :
# Tests in static libraries might not get registered, see https://github.com/onqtam/doctest/blob/master/doc/markdown/faq.md#why-are-my-tests-in-a-static-library-not-getting-registered
# For this reason, and because it is interesting to have individual
# test executables for each library, it is suggested not to put tests directly in the libraries (even though doctest advocates this usage)
# Creating multiple executables is of course not mandatory, and one could use the same executable with various command lines to filter what tests to run.

add_executable(D2GameTests D2GameTests.cpp)

# Ai
target_sources(D2GameTests
  PRIVATE
    AI/AiBaalTests.cpp
    AI/AiGeneralTests.cpp
    AI/AiTacticsTests.cpp
    AI/AiThinkTests.cpp
    AI/AiUtilTests.cpp
)

# Debug
target_sources(D2GameTests
  PRIVATE
    DEBUG/DebugTests.cpp
)

# Game
target_sources(D2GameTests
  PRIVATE
    GAME/ArenaTests.cpp
    GAME/CCmdTests.cpp
    GAME/ClientsTests.cpp
    GAME/EventTests.cpp
    GAME/GameTests.cpp
    GAME/LevelTests.cpp
    GAME/SCmdTests.cpp
    GAME/TargetsTests.cpp
    GAME/TaskTests.cpp
)

# Inventory
target_sources(D2GameTests
  PRIVATE
    INVENTORY/InvModeTests.cpp
)

# Items
target_sources(D2GameTests
  PRIVATE
    ITEMS/ItemModeTests.cpp
    ITEMS/ItemsTests.cpp
    ITEMS/ItemsMagicTests.cpp
)

# Missiles
target_sources(D2GameTests
  PRIVATE
    MISSILES/MissilesTests.cpp
    MISSILES/MissModeTests.cpp
)

# Monster
target_sources(D2GameTests
  PRIVATE
    MONSTER/MonsterTests.cpp
    MONSTER/MonsterAITests.cpp
    MONSTER/MonsterChooseTests.cpp
    MONSTER/MonsterModeTests.cpp
    MONSTER/MonsterMsgTests.cpp
    MONSTER/MonsterRegionTests.cpp
    MONSTER/MonsterSpawnTests.cpp
    MONSTER/MonsterUniqueTests.cpp
)

# Objects
target_sources(D2GameTests
  PRIVATE
    OBJECTS/ObjectsTests.cpp
    OBJECTS/ObjEvalTests.cpp
    OBJECTS/ObjModeTests.cpp
    OBJECTS/ObjRgnTests.cpp
)

# Player
target_sources(D2GameTests
  PRIVATE
    PLAYER/PartyScreenTests.cpp
    PLAYER/PlayerTests.cpp
    PLAYER/PlayerListTests.cpp
    PLAYER/PlayerPetsTests.cpp
    PLAYER/PlayerStatsTests.cpp
    PLAYER/PlrIntroTests.cpp
    PLAYER/PlrModesTests.cpp
    PLAYER/PlrMsgTests.cpp
    PLAYER/PlrSaveTests.cpp
    PLAYER/PlrSave2Tests.cpp
    PLAYER/PlrTradeTests.cpp
)

# Quests
target_sources(D2GameTests
  PRIVATE
    QUESTS/QuestsTests.cpp
    QUESTS/QuestsFXTests.cpp
)

# Quests - Act1
target_sources(D2GameTests
  PRIVATE
    QUESTS/ACT1/A1IntroTests.cpp
    QUESTS/ACT1/A1Q0Tests.cpp
    QUESTS/ACT1/A1Q1Tests.cpp
    QUESTS/ACT1/A1Q2Tests.cpp
    QUESTS/ACT1/A1Q3Tests.cpp
    QUESTS/ACT1/A1Q4Tests.cpp
    QUESTS/ACT1/A1Q5Tests.cpp
    QUESTS/ACT1/A1Q6Tests.cpp
    QUESTS/ACT1/A1Q7Tests.cpp
)

# Quests - Act2
target_sources(D2GameTests
  PRIVATE
    QUESTS/ACT2/A2IntroTests.cpp
    QUESTS/ACT2/A2Q0Tests.cpp
    QUESTS/ACT2/A2Q1Tests.cpp
    QUESTS/ACT2/A2Q2Tests.cpp
    QUESTS/ACT2/A2Q3Tests.cpp
    QUESTS/ACT2/A2Q4Tests.cpp
    QUESTS/ACT2/A2Q5Tests.cpp
    QUESTS/ACT2/A2Q6Tests.cpp
    QUESTS/ACT2/A2Q7Tests.cpp
    QUESTS/ACT2/A2Q8Tests.cpp
)

# Quests - Act3
target_sources(D2GameTests
  PRIVATE
    QUESTS/ACT3/A3IntroTests.cpp
    QUESTS/ACT3/A3Q0Tests.cpp
    QUESTS/ACT3/A3Q1Tests.cpp
    QUESTS/ACT3/A3Q2Tests.cpp
    QUESTS/ACT3/A3Q3Tests.cpp
    QUESTS/ACT3/A3Q4Tests.cpp
    QUESTS/ACT3/A3Q5Tests.cpp
    QUESTS/ACT3/A3Q6Tests.cpp
    QUESTS/ACT3/A3Q7Tests.cpp
)

# Quests - Act4
target_sources(D2GameTests
  PRIVATE
    QUESTS/ACT4/A4Q0Tests.cpp
    QUESTS/ACT4/A4Q1Tests.cpp
    QUESTS/ACT4/A4Q2Tests.cpp
    QUESTS/ACT4/A4Q3Tests.cpp
    QUESTS/ACT4/A4Q4Tests.cpp
)

# Quests - Act5
target_sources(D2GameTests
  PRIVATE
    QUESTS/ACT5/A5IntroTests.cpp
    QUESTS/ACT5/A5Q1Tests.cpp
    QUESTS/ACT5/A5Q2Tests.cpp
    QUESTS/ACT5/A5Q3Tests.cpp
    QUESTS/ACT5/A5Q4Tests.cpp
    QUESTS/ACT5/A5Q5Tests.cpp
    QUESTS/ACT5/A5Q6Tests.cpp
)

# Unit
target_sources(D2GameTests
  PRIVATE
    UNIT/FriendlyTests.cpp
    UNIT/PartyTests.cpp
    UNIT/SUnitTests.cpp
    UNIT/SUnitDmgTests.cpp
    UNIT/SUnitEventTests.cpp
    UNIT/SUnitInactiveTests.cpp
    UNIT/SUnitMsgTests.cpp
    UNIT/SUnitNpcTests.cpp
    UNIT/SUnitProxyTests.cpp
)

# Skills
target_sources(D2GameTests
  PRIVATE
    SKILLS/SkillAmaTests.cpp
    SKILLS/SkillAssTests.cpp
    SKILLS/SkillBarTests.cpp
    SKILLS/SkillDruidTests.cpp
    SKILLS/SkillItemTests.cpp
    SKILLS/SkillMonstTests.cpp
    SKILLS/SkillNecTests.cpp
    SKILLS/SkillPalTests.cpp
    SKILLS/SkillsTests.cpp
    SKILLS/SkillSorTests.cpp
)

get_target_property(D2GameTestsSources D2GameTests SOURCES)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${D2GameTestsSources})

target_link_libraries(D2GameTests PRIVATE doctest::doctest TestDefinitions TestUtilities VisitorFramework ${D2GameImplName} D2CommonDefinitions D2Common)
target_compile_features(D2GameTests PRIVATE cxx_std_17)

set_target_properties(D2GameTests PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../workingDirectory
)

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME D2GameTests.unittests
    COMMAND D2GameTests ${TEST_RUNNER_PARAMS}
    WORKING_DIRECTORY $<TARGET_PROPERTY:D2GameTests,VS_DEBUGGER_WORKING_DIRECTORY>
)
