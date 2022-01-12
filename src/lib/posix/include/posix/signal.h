/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: signal.h
 * Description		: Signals (Signals are currently not implemented in CC+POSIX)
 *                  : http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/signal.h.html
 *
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define _CC_POSIX_SIGNAL_H_

/**
 * @name Values of sigev_notify.
 */
/**@{ */
#define SIGEV_NONE      0 /**< No asynchronous notification is delivered when the event of interest occurs. */
#define SIGEV_SIGNAL    1 /**< A queued signal, with an application-defined value, is generated when the event of interest occurs. Not supported. */
#define SIGEV_THREAD    2 /**< A notification function is called to perform notification. */
/**@} */

/**
 * @brief Signal value.
 */
union sigval
{
    int sival_int;    /**< Integer signal value. */
    void * sival_ptr; /**< Pointer signal value. */
};

/**
 * @brief Signal event structure.
 */
struct sigevent
{
    int sigev_notify;                                 /**< Notification type. A value of SIGEV_SIGNAL is not supported. */
    int sigev_signo;                                  /**< Signal number. This member is ignored. */
    union sigval sigev_value;                         /**< Signal value. Only the sival_ptr member is used. */
    void ( * sigev_notify_function )( union sigval ); /**< Notification function. */
    pthread_attr_t * sigev_notify_attributes;         /**< Notification attributes. */
};
