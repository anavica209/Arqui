#ifndef __video_h__
#define __video_h__

#include "defs.h"
#include "console.h"

int init_video();

int set_terminal(int which);

int refresh_video();

int update_video(int pointer, size_t lenght);

#endif //__video_h__
