D2MOO_prepare_targets(Bnclient)

target_link_libraries(${BnclientImplName} PRIVATE D2CommonDefinitions Fog Storm wsock32 user32)

target_sources(${BnclientImplName}
  PRIVATE
    # Official file names
    src/BnConnect.cpp
    src/BnDownload.cpp
    src/BNetGW.cpp
    src/BnMessQueue.cpp
    src/BNNews.cpp
    src/BnSend.cpp
    src/BnCache.cpp
    src/Grid.cpp
    src/SRP/SHA.cpp
    src/SRP/SRP.cpp

    # Made up file names
    src/BnClient.cpp
    src/BnImports.cpp
    src/BnLog.cpp
    src/BnRecv.cpp
    src/BnSRP.cpp

    # Headers
    include/BnCache.h
    include/BnConnect.h
    include/BnDownload.h
    include/BNetGW.h
    include/BnImports.h
    include/BnLog.h
    include/BnMessQueue.h
    include/BNNews.h
    include/BnRecv.h
    include/BnSend.h
    include/BnSRP.h
    include/Grid.h
    include/SRP/SHA.h
    include/SRP/SRP.h
)

D2MOO_target_source_group(Bnclient)
