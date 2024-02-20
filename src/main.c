// C standard headers
#include <stdio.h>
// Local headers
#include <result.h>
#include <dimension.h>
#include <windower.h>
#include <renderer.h>

#define INIT_FAIL                       "Windower failed to initialize"
#define WINDOW_FAIL                     "Windower failed to create window"

#define FATAL_ERR_FMT                   "FATAL ERROR: %s - %s\nExiting program\n"
#define CHECK_RESULT(_process, _result, _actions)   if(_result.code != 0) { \
                                                        fprintf(stderr, FATAL_ERR_FMT, _process, _result.msg); \
                                                        _actions; \
                                                        return _result.code; \
                                                    }
                                        
int main(void) {
    Result retData = STANDARD_SUCCESS;
    retData = windower_init();
    CHECK_RESULT(INIT_FAIL, retData,);

    WinTools toolSet = {
        NULL,
        renderer_draw,
        NULL
    };

    retData = window_create((Dimension){ 600, 480 }, "TEST ONE", toolSet, NULL);
    CHECK_RESULT(WINDOW_FAIL, retData, windower_cleanup());
    retData = window_create((Dimension){ 600, 480 }, "TEST TWO", toolSet, NULL);
    CHECK_RESULT(WINDOW_FAIL, retData, windower_cleanup());
    
    windower_loop();
    windower_cleanup();

    return 0;
}