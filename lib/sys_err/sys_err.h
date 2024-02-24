/**
 * @file sys_err.h
 * @author jake-is-ESD-protected
 * @date 2024-02-24
 * @brief Top-level ubiquitous error handling.
 *
 * 
 */

#ifndef _SYS_ERR_H_
#define _SYS_ERR_H_

/// @brief      Standard top-level error handler.
/// @attention  Implementation depends on SYS_USE_LED_LOOP_ERR_HANDLER
///             `SYS_USE_LED_LOOP_ERR_HANDLER` in `sys_settings.h` 
void sys_err_handler(void);

#endif // _SYS_ERR_H_
