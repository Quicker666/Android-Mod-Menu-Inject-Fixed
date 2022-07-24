#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>

#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include <SOCKET/server.h>
#include "KittyMemory/MemoryPatch.h"

//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")

#include "Includes/Macros.h"


enum Mode {
    InitMode = 1,
    HackMode = 2,
    StopMode = 3,
    EspMode = 99,
};


struct Request {
    int Mode;
    bool boolean;
    int value;
    int screenWidth;
    int screenHeight;
};

#define maxplayerCount 54

struct PlayerData {
    char PlayerName[64];
    // string *Test;
    float Health;
    float Distance2;
    bool get_IsDieing;
    bool isBot;
    Vector3 CloseEnemyHeadLocation;
    Vector3 HeadLocation;
    Vector3 ToeLocation;
    Vector2 RShoulder;
    Vector3 LShoulder;
    Vector3 Toe;
    Vector3 Hip;
    Vector3 Head;
    int x;
    int y;
    int z;
    int id;
    int h;
    char debug[60];
};

struct Response {
    bool Success;
    int PlayerCount;
    PlayerData Players[maxplayerCount];
};

SocketServer server;

int InitServer() {
    if (!server.Create()) {
        return -1;
    }
    if (!server.Bind()) {
        return -1;
    }
    if (!server.Listen()) {
        return -1;
    }
    return 0;
}
enum f {
    f1 = 4,
    f2 = 5,
    f3 = 6,
    f4 = 7,
    f5 = 8,
    f6 = 9,
    f7 = 10,
    f8 = 11,
    f9 = 12,
    f10 = 13,
};

struct My_Patches {
    MemoryPatch GodMode,
    GodMode2,
    SliderExample;
} hexPatches;

bool feature1, feature2;
int sliderValue = 1, level = 0;
void *instanceBtn;



void createDataList(Response& response) {}


void *CreateServer(void *) {
    if (InitServer() == 0) {
        if (server.Accept()) {
            Request request {};
            while (server.receive((void*)&request) > 0) {
                Response response {};
                if (request.Mode == Mode::InitMode) {
                    response.Success = true;
                } else if (request.Mode == Mode::HackMode) {

                    response.Success = true;
                } else if (request.Mode == Mode::EspMode) {

                    createDataList(response);
                    response.Success = true;
                } else if (request.Mode == f::f1) {

                    feature2 = request.boolean;

                    if (feature2) {
                        hexPatches.GodMode.Modify();
                    } else {
                        hexPatches.GodMode.Restore();
                    }
                    response.Success = true;
                }
                server.sendX((void*)& response, sizeof(response));
            }
        }
    }
    return nullptr;
}


void* Thread (void *) {
    ProcMap il2cppMap;
    do {
        il2cppMap = KittyMemory::getLibraryMap("libil2cpp.so");
        sleep(1);
    } while (!il2cppMap.isValid());

#if defined(__aarch64__)

#else
    hexPatches.GodMode = MemoryPatch::createWithHex(targetLibName,

               +                                     string2Offset(OBFUSCATE("0x45351C")),OBFUSCATE("00 48 2D E9 0D B0 A0 E1 08 D0 4D E2 64 10 A0 E3 01 20 A0 E3 32 05 00 EB 0B D0 A0 E1 00 88 BD E8 1E FF 2F E1"));

    LOGI(OBFUSCATE("Done"));
  #endif

    return NULL;

}



__attribute__((constructor))
void lib_main() {
    pthread_t PidThread;
    pthread_create(&PidThread, NULL, Thread, NULL);
    pthread_t ptid;
    pthread_create(&ptid, nullptr, CreateServer, nullptr);

}
