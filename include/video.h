#ifndef __video_h__
#define __video_h__

typedef struct {
} Console;

int init_video();

int set_terminal(Console);

int refresh_video();

int update_video(int, int, size_t);

#endif //__video_h__
