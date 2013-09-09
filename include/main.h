
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define WEH_UPDATE_STD_OUTPUTS
#define WEH_FILE_MODE "a"
#define WEH_FILE_MODE_CLEAN "wt"

#define WEH_STDOUT "output\\stdout.txt"
#define WEH_STDERR "output\\stderr.txt"

/**
 * Exit Applicaition
 **/
void weh_exit();

/**
 * Change standar outputs
 **/
void change_std_outputs();

#ifdef WEH_UPDATE_STD_OUTPUTS
#define UPDATE_STD_OUTPUTS change_std_outputs()
#else
#define UPDATE_STD_OUTPUTS
#endif

#define QUEUE_UP atexit(weh_exit);

#endif // MAIN_H_INCLUDED
