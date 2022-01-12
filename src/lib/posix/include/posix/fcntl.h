/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: fcntl.h
 * Description		: File control options.
 * 			: http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/fcntl.h.html
 *
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define _CC_POSIX_FCNTL_H_

/**
 * @name File creation flags for use in the oflag value to open() and openat().
 */
/**@{ */
#define O_CLOEXEC      0x0001 /**< Close the file descriptor upon exec(). */
#define O_CREAT        0x0002 /**< Create file if it does not exist. */
#define O_DIRECTORY    0x0004 /**< Fail if file is a non-directory file. */
#define O_EXCL         0x0008 /**< Exclusive use flag. */
#define O_NOCTTY       0x0010 /**< Do not assign controlling terminal. */
#define O_NOFOLLOW     0x0020 /**< Do not follow symbolic links. */
#define O_TRUNC        0x0040 /**< Truncate flag. */
#define O_TTY_INIT     0x0080 /**< termios structure provides conforming behavior. */
/**@} */

/**
 * @name File status flags for open(), openat(), and fcntl().
 */
/**@{ */
#define O_APPEND      0x0100 /**< Set append mode. */
#define O_DSYNC       0x0200 /**< Write according to synchronized I/O data integrity completion. */
#define O_NONBLOCK    0x0400 /**< Non-blocking mode. */
#define O_RSYNC       0x0800 /**< Synchronized read I/O operations. */
#define O_SYNC        0x0200 /**< Write according to synchronized I/O file integrity completion. */
/**@} */

/**
 * @name Mask for file access modes.
 */
/**@{ */
#define O_ACCMODE    0xF000
/**@} */

/**
 * @name File access modes for open(), openat(), and fcntl().
 */
/**@{ */
#define O_EXEC      0x1000  /**< Open for execute only (non-directory files). */
#define O_RDONLY    0x2000  /**< Open for reading only. */
#define O_RDWR      0xA000  /**< Open for reading and writing. */
#define O_SEARCH    0x4000  /**< Open directory for search only. */
#define O_WRONLY    0x8000  /**< Open for writing only. */
/**@} */
