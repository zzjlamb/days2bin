#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#ifdef __cplusplus
extern "C" {
#endif

// Shutdown if no activity after this time
#define ACCESS_POINT_TIMEOUT_MS 120*1000        // 2 minutes should be sufficient

int access_point();

#ifdef __cplusplus
}
#endif

#endif