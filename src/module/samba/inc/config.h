/* include/config.h.  Generated from config.h.in by configure.  */
/* include/config.h.in.  Generated from configure.in by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Whether the host os is aix */
/* #undef AIX */

/* Whether the AIX send_file() API is available */
/* #undef AIX_SENDFILE_API */

/* Does extattr API work */
/* #undef BROKEN_EXTATTR */

/* Does getgrnam work correctly */
/* #undef BROKEN_GETGRNAM */

/* Whether the nisplus include files are broken */
/* #undef BROKEN_NISPLUS_INCLUDE_FILES */

/* Broken RedHat 7.2 system header files */
/* #undef BROKEN_REDHAT_7_SYSTEM_HEADERS */

/* Broken RHEL5 sys/capability.h */
/* #undef BROKEN_RHEL5_SYS_CAP_HEADER */

/* Does strndup work correctly */
/* #undef BROKEN_STRNDUP */

/* Does strnlen work correctly */
/* #undef BROKEN_STRNLEN */

/* Does this system use unicode compose characters */
/* #undef BROKEN_UNICODE_COMPOSE_CHARACTERS */

/* Whether to enable cluster extensions */
/* #undef CLUSTER_SUPPORT */

/* Whether the compiler supports the LL prefix on long long integers */
#define COMPILER_SUPPORTS_LL 1

/* Marker for samba's config.h */
#define CONFIG_H_IS_FROM_SAMBA 1

/* Whether the host os is Darwin/MacOSX */
/* #undef DARWINOS */

/* Default display charset name */
#define DEFAULT_DISPLAY_CHARSET "ASCII"

/* Default dos charset name */
#define DEFAULT_DOS_CHARSET "CP850"

/* Default unix charset name */
#define DEFAULT_UNIX_CHARSET "UTF-8"

/* Whether dlopen takes unsigned int flags */
/* #undef DLOPEN_TAKES_UNSIGNED_FLAGS */

/* Define to check invariants around some common functions */
/* #undef DMALLOC_FUNC_CHECK */

/* Defined if running in the build farm */
/* #undef ENABLE_BUILD_FARM_HACKS */

/* Define to turn on dmalloc debugging */
/* #undef ENABLE_DMALLOC */

/* Whether to use fully FHS-compatible paths */
/* #undef FHS_COMPATIBLE */

/* Whether the host os is FreeBSD */
/* #undef FREEBSD */

/* Whether the FreeBSD sendfile() API is available */
/* #undef FREEBSD_SENDFILE_API */

/* Whether acl_get_perm_np() is available */
#define HAVE_ACL_GET_PERM_NP 1

/* Define to 1 if you have the <acl/libacl.h> header file. */
/* #undef HAVE_ACL_LIBACL_H */

/* Whether the krb5_address struct has a addrtype property */
/* #undef HAVE_ADDRTYPE_IN_KRB5_ADDRESS */

/* Whether the krb5_address struct has a addr_type property */
/* #undef HAVE_ADDR_TYPE_IN_KRB5_ADDRESS */

/* Define to 1 if you have the `add_proplist_entry' function. */
/* #undef HAVE_ADD_PROPLIST_ENTRY */

/* Define to 1 if you have the <afs/afs.h> header file. */
/* #undef HAVE_AFS_AFS_H */

/* Define to 1 if you have the <afs.h> header file. */
/* #undef HAVE_AFS_H */

/* Whether 64 bit aio is available */
/* #undef HAVE_AIOCB64 */

/* Have aio_cancel */
/* #undef HAVE_AIO_CANCEL */

/* Have aio_cancel64 */
/* #undef HAVE_AIO_CANCEL64 */

/* Have aio_error */
/* #undef HAVE_AIO_ERROR */

/* Have aio_error64 */
/* #undef HAVE_AIO_ERROR64 */

/* Have aio_fsync */
/* #undef HAVE_AIO_FSYNC */

/* Have aio_fsync64 */
/* #undef HAVE_AIO_FSYNC64 */

/* Define to 1 if you have the <aio.h> header file. */
#define HAVE_AIO_H 1

/* Have aio_read */
/* #undef HAVE_AIO_READ */

/* Have aio_read64 */
/* #undef HAVE_AIO_READ64 */

/* Have aio_return */
/* #undef HAVE_AIO_RETURN */

/* Have aio_return64 */
/* #undef HAVE_AIO_RETURN64 */

/* Have aio_suspend */
/* #undef HAVE_AIO_SUSPEND */

/* Have aio_suspend64 */
/* #undef HAVE_AIO_SUSPEND64 */

/* Have aio_write */
/* #undef HAVE_AIO_WRITE */

/* Have aio_write64 */
/* #undef HAVE_AIO_WRITE64 */

/* Whether AIX ACLs are available */
/* #undef HAVE_AIX_ACLS */

/* Define to 1 if you have the <alloca.h> header file. */
#define HAVE_ALLOCA_H 1

/* Whether the AP_OPTS_USE_SUBKEY ap option is available */
/* #undef HAVE_AP_OPTS_USE_SUBKEY */

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* check for <asm/types.h> */
/* #undef HAVE_ASM_TYPES_H */

/* Define to 1 if you have the <asm/unistd.h> header file. */
/* #undef HAVE_ASM_UNISTD_H */

/* Define to 1 if you have the `asprintf' function. */
/* #undef HAVE_ASPRINTF */

/* Define to 1 if you have the `atexit' function. */
#define HAVE_ATEXIT 1

/* Define to 1 if you have the `attropen' function. */
/* #undef HAVE_ATTROPEN */

/* Define to 1 if you have the `attr_get' function. */
/* #undef HAVE_ATTR_GET */

/* Define to 1 if you have the `attr_getf' function. */
/* #undef HAVE_ATTR_GETF */

/* Define to 1 if you have the `attr_list' function. */
/* #undef HAVE_ATTR_LIST */

/* Define to 1 if you have the `attr_listf' function. */
/* #undef HAVE_ATTR_LISTF */

/* Define to 1 if you have the `attr_remove' function. */
/* #undef HAVE_ATTR_REMOVE */

/* Define to 1 if you have the `attr_removef' function. */
/* #undef HAVE_ATTR_REMOVEF */

/* Define to 1 if you have the `attr_set' function. */
/* #undef HAVE_ATTR_SET */

/* Define to 1 if you have the `attr_setf' function. */
/* #undef HAVE_ATTR_SETF */

/* Define to 1 if you have the <attr/xattr.h> header file. */
/* #undef HAVE_ATTR_XATTR_H */

/* Define to 1 if you have the <avahi-client/client.h> header file. */
/* #undef HAVE_AVAHI_CLIENT_CLIENT_H */

/* Define to 1 if you have the <avahi-common/watch.h> header file. */
/* #undef HAVE_AVAHI_COMMON_WATCH_H */

/* Define to 1 if you have the `backtrace_symbols' function. */
/* #undef HAVE_BACKTRACE_SYMBOLS */

/* Define to 1 if you have the `ber_scanf' function. */
/* #undef HAVE_BER_SCANF */

/* Define to 1 if you have the `ber_sockbuf_add_io' function. */
/* #undef HAVE_BER_SOCKBUF_ADD_IO */

/* What header to include for iconv() function: biconv.h */
/* #undef HAVE_BICONV */

/* Whether bigcrypt is available */
/* #undef HAVE_BIGCRYPT */

/* Define to 1 if you have the `bindtextdomain' function. */
/* #undef HAVE_BINDTEXTDOMAIN */

/* Define to 1 if the system has the type `blkcnt_t'. */
#define HAVE_BLKCNT_T 1

/* Define to 1 if the system has the type `blksize_t'. */
#define HAVE_BLKSIZE_T 1

/* Whether the bool type is available */
#define HAVE_BOOL 1

/* Whether fcntl64 locks are broken */
/* #undef HAVE_BROKEN_FCNTL64_LOCKS */

/* Whether getgroups is broken */
/* #undef HAVE_BROKEN_GETGROUPS */

/* Whether we have a broken posix_fallocate */
/* #undef HAVE_BROKEN_POSIX_FALLOCATE */

/* Whether readdir() returns the wrong name offset */
/* #undef HAVE_BROKEN_READDIR_NAME */

/* Whether the readlink syscall is broken */
/* #undef HAVE_BROKEN_READLINK */

/* Define to 1 if you have the `bzero' function. */
#define HAVE_BZERO 1

/* Whether there is a C99 compliant vsnprintf */
/* #undef HAVE_C99_VSNPRINTF */

/* Whether cap_get_proc is available */
/* #undef HAVE_CAP_GET_PROC */

/* Define to 1 if you have the <CFStringEncodingConverter.h> header file. */
/* #undef HAVE_CFSTRINGENCODINGCONVERTER_H */

/* Whether the krb5_checksum struct has a checksum property */
/* #undef HAVE_CHECKSUM_IN_KRB5_CHECKSUM */

/* Define to 1 if you have the `chflags' function. */
/* #undef HAVE_CHFLAGS */

/* Define to 1 if you have the `chmod' function. */
#define HAVE_CHMOD 1

/* Define to 1 if you have the `chown' function. */
#define HAVE_CHOWN 1

/* Define to 1 if you have the `chroot' function. */
#define HAVE_CHROOT 1

/* Define to 1 if you have the `chsize' function. */
/* #undef HAVE_CHSIZE */

/* Define to 1 if there is support for clock_gettime */
#define HAVE_CLOCK_GETTIME 1

/* Whether the clock_gettime clock ID CLOCK_MONOTONIC is available */
#define HAVE_CLOCK_MONOTONIC 1

/* Whether the clock_gettime clock ID CLOCK_PROCESS_CPUTIME_ID is available */
#define HAVE_CLOCK_PROCESS_CPUTIME_ID 1

/* Whether the clock_gettime clock ID CLOCK_REALTIME is available */
#define HAVE_CLOCK_REALTIME 1

/* Define to 1 if you have the `closedir64' function. */
/* #undef HAVE_CLOSEDIR64 */

/* Whether or not we have comparison_fn_t */
/* #undef HAVE_COMPARISON_FN_T */

/* Define to 1 if you have the <compat.h> header file. */
/* #undef HAVE_COMPAT_H */

/* Whether the compiler will optimize out function calls */
#define HAVE_COMPILER_WILL_OPTIMIZE_OUT_FNS 1

/* Define to 1 if you have the <com_err.h> header file. */
/* #undef HAVE_COM_ERR_H */

/* Whether the system has connect() */
#define HAVE_CONNECT 1

/* Define to 1 if you have the `copy_Authenticator' function. */
/* #undef HAVE_COPY_AUTHENTICATOR */

/* Define to 1 if you have the <CoreFoundation/CFStringEncodingConverter.h>
   header file. */
/* #undef HAVE_COREFOUNDATION_CFSTRINGENCODINGCONVERTER_H */

/* Define to 1 if you have the `creat64' function. */
/* #undef HAVE_CREAT64 */

/* Whether the system has the crypt() function */
#define HAVE_CRYPT 1

/* Define to 1 if you have the `crypt16' function. */
/* #undef HAVE_CRYPT16 */

/* Define to 1 if you have the <crypt.h> header file. */
/* #undef HAVE_CRYPT_H */

/* Whether CTDB_CONTROL_SCHEDULE_FOR_DELETION() is available */
/* #undef HAVE_CTDB_CONTROL_SCHEDULE_FOR_DELETION_DECL */

/* Whether CTDB_CONTROL_TRANS3_COMMIT() is available */
/* #undef HAVE_CTDB_CONTROL_TRANS3_COMMIT_DECL */

/* Define to 1 if you have the <ctdb.h> header file. */
/* #undef HAVE_CTDB_H */

/* Define to 1 if you have the <ctdb_private.h> header file. */
/* #undef HAVE_CTDB_PRIVATE_H */

/* Define to 1 if you have the <ctype.h> header file. */
#define HAVE_CTYPE_H 1

/* Whether we have CUPS */
/* #undef HAVE_CUPS */

/* Define to 1 if you have the <cups/cups.h> header file. */
/* #undef HAVE_CUPS_CUPS_H */

/* Define to 1 if you have the <cups/language.h> header file. */
/* #undef HAVE_CUPS_LANGUAGE_H */

/* Whether to use the Darwin-specific initgroups system call */
/* #undef HAVE_DARWIN_INITGROUPS */

/* Define to 1 if you have the declaration of `asprintf', and to 0 if you
   don't. */
#define HAVE_DECL_ASPRINTF 0

/* Define to 1 if you have the declaration of
   `krb5_auth_con_set_req_cksumtype', and to 0 if you don't. */
/* #undef HAVE_DECL_KRB5_AUTH_CON_SET_REQ_CKSUMTYPE */

/* Define to 1 if you have the declaration of `krb5_get_credentials_for_user',
   and to 0 if you don't. */
/* #undef HAVE_DECL_KRB5_GET_CREDENTIALS_FOR_USER */

/* Define to 1 if you have the declaration of `rl_event_hook', and to 0 if you
   don't. */
#define HAVE_DECL_RL_EVENT_HOOK 1

/* Define to 1 if you have the declaration of `snprintf', and to 0 if you
   don't. */
#define HAVE_DECL_SNPRINTF 1

/* Define to 1 if you have the declaration of `vasprintf', and to 0 if you
   don't. */
#define HAVE_DECL_VASPRINTF 0

/* Define to 1 if you have the declaration of `vsnprintf', and to 0 if you
   don't. */
#define HAVE_DECL_VSNPRINTF 1

/* Define to 1 if you have the `delproplist' function. */
/* #undef HAVE_DELPROPLIST */

/* Define to 1 if you have the `des_set_key' function. */
/* #undef HAVE_DES_SET_KEY */

/* Whether the 'dev64_t' type is available */
/* #undef HAVE_DEV64_T */

/* Whether the major macro for dev_t is available */
/* #undef HAVE_DEVICE_MAJOR_FN */

/* Whether the minor macro for dev_t is available */
/* #undef HAVE_DEVICE_MINOR_FN */

/* Define to 1 if you have the `devnm' function. */
/* #undef HAVE_DEVNM */

/* Define to 1 if you have the <devnm.h> header file. */
/* #undef HAVE_DEVNM_H */

/* Define to 1 if you have the `dgettext' function. */
/* #undef HAVE_DGETTEXT */

/* Define to 1 if you have the <direct.h> header file. */
/* #undef HAVE_DIRECT_H */

/* Whether dirent has a d_off member */
/* #undef HAVE_DIRENT_D_OFF */

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the `dirfd' function. */
#define HAVE_DIRFD 1

/* Whether dirfd() is available */
/* #undef HAVE_DIRFD_DECL */

/* Define to 1 if you have the `dlclose' function. */
#define HAVE_DLCLOSE 1

/* Define to 1 if you have the `dlerror' function. */
#define HAVE_DLERROR 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the `dlopen' function. */
#define HAVE_DLOPEN 1

/* Define to 1 if you have the `dlsym' function. */
#define HAVE_DLSYM 1

/* Define to 1 if you have the <dl.h> header file. */
/* #undef HAVE_DL_H */

/* Define to 1 if you have the <dmapi.h> header file. */
/* #undef HAVE_DMAPI_H */

/* Define to 1 if you have the `DNSServiceRegister' function. */
/* #undef HAVE_DNSSERVICEREGISTER */

/* Define to 1 if you have the <dns_sd.h> header file. */
/* #undef HAVE_DNS_SD_H */

/* Define to 1 if you have the `dprintf' function. */
/* #undef HAVE_DPRINTF */

/* struct dqblk .dqb_fsoftlimit */
/* #undef HAVE_DQB_FSOFTLIMIT */

/* Define to 1 if you have the `dup2' function. */
#define HAVE_DUP2 1

/* Whether the ENCTYPE_AES128_CTS_HMAC_SHA1_96 key type definition is
   available */
/* #undef HAVE_ENCTYPE_AES128_CTS_HMAC_SHA1_96 */

/* Whether the ENCTYPE_AES256_CTS_HMAC_SHA1_96 key type definition is
   available */
/* #undef HAVE_ENCTYPE_AES256_CTS_HMAC_SHA1_96 */

/* Whether the ENCTYPE_ARCFOUR_HMAC key type definition is available */
/* #undef HAVE_ENCTYPE_ARCFOUR_HMAC */

/* Whether the ENCTYPE_ARCFOUR_HMAC_MD5 key type definition is available */
/* #undef HAVE_ENCTYPE_ARCFOUR_HMAC_MD5 */

/* Define to 1 if you have the `endmntent' function. */
/* #undef HAVE_ENDMNTENT */

/* Define to 1 if you have the `endnetgrent' function. */
/* #undef HAVE_ENDNETGRENT */

/* If endnetgrent prototype is defined */
#define HAVE_ENDNETGRENT_PROTOTYPE 1

/* Whether environ() is available */
#define HAVE_ENVIRON_DECL 1

/* Whether epoll available */
/* #undef HAVE_EPOLL */

/* Define to 1 if you have the `epoll_create' function. */
/* #undef HAVE_EPOLL_CREATE */

/* Whether errno() is available */
#define HAVE_ERRNO_DECL 1

/* Whether the EncryptedData struct has a etype property */
/* #undef HAVE_ETYPE_IN_ENCRYPTEDDATA */

/* Define to 1 if you have the <execinfo.h> header file. */
/* #undef HAVE_EXECINFO_H */

/* Define to 1 if you have the `execl' function. */
#define HAVE_EXECL 1

/* Whether large file support can be enabled */
/* #undef HAVE_EXPLICIT_LARGEFILE_SUPPORT */

/* Define to 1 if you have the `extattr_delete_fd' function. */
/* #undef HAVE_EXTATTR_DELETE_FD */

/* Define to 1 if you have the `extattr_delete_file' function. */
/* #undef HAVE_EXTATTR_DELETE_FILE */

/* Define to 1 if you have the `extattr_delete_link' function. */
/* #undef HAVE_EXTATTR_DELETE_LINK */

/* Define to 1 if you have the `extattr_get_fd' function. */
/* #undef HAVE_EXTATTR_GET_FD */

/* Define to 1 if you have the `extattr_get_file' function. */
/* #undef HAVE_EXTATTR_GET_FILE */

/* Define to 1 if you have the `extattr_get_link' function. */
/* #undef HAVE_EXTATTR_GET_LINK */

/* Define to 1 if you have the `extattr_list_fd' function. */
/* #undef HAVE_EXTATTR_LIST_FD */

/* Define to 1 if you have the `extattr_list_file' function. */
/* #undef HAVE_EXTATTR_LIST_FILE */

/* Define to 1 if you have the `extattr_list_link' function. */
/* #undef HAVE_EXTATTR_LIST_LINK */

/* Define to 1 if you have the `extattr_set_fd' function. */
/* #undef HAVE_EXTATTR_SET_FD */

/* Define to 1 if you have the `extattr_set_file' function. */
/* #undef HAVE_EXTATTR_SET_FILE */

/* Define to 1 if you have the `extattr_set_link' function. */
/* #undef HAVE_EXTATTR_SET_LINK */

/* Whether the krb5_error struct has a e_data pointer */
/* #undef HAVE_E_DATA_POINTER_IN_KRB5_ERROR */

/* Define to 1 if you have the `fallocate' function. */
/* #undef HAVE_FALLOCATE */

/* Define to 1 if you have the `fallocate64' function. */
/* #undef HAVE_FALLOCATE64 */

/* Define to 1 if there is support for FAMNoExists */
/* #undef HAVE_FAMNOEXISTS */

/* Define to 1 if there is support for FAMOpen2 */
/* #undef HAVE_FAMOPEN2 */

/* Define to 1 if you have the <fam.h> header file. */
/* #undef HAVE_FAM_H */

/* Whether fam.h contains a typedef for enum FAMCodes */
/* #undef HAVE_FAM_H_FAMCODES_TYPEDEF */

/* Define to 1 if you have the `fchmod' function. */
#define HAVE_FCHMOD 1

/* Define to 1 if you have the `fchown' function. */
#define HAVE_FCHOWN 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Whether fcntl locking is available */
/* #undef HAVE_FCNTL_LOCK */

/* Define to 1 if you have the `fcvt' function. */
/* #undef HAVE_FCVT */

/* Define to 1 if you have the `fcvtl' function. */
/* #undef HAVE_FCVTL */

/* Define to 1 if you have the `fdatasync' function. */
#define HAVE_FDATASYNC 1

/* Whether fdatasync() is available */
#define HAVE_FDATASYNC_DECL 1

/* Define to 1 if you have the `fdelproplist' function. */
/* #undef HAVE_FDELPROPLIST */

/* Define to 1 if you have the `fdopendir' function. */
/* #undef HAVE_FDOPENDIR */

/* Define to 1 if you have the `fdopendir64' function. */
/* #undef HAVE_FDOPENDIR64 */

/* Define to 1 if you have the `fgetea' function. */
/* #undef HAVE_FGETEA */

/* Define to 1 if you have the `fgetproplist' function. */
/* #undef HAVE_FGETPROPLIST */

/* Define to 1 if you have the `fgetxattr' function. */
/* #undef HAVE_FGETXATTR */

/* Define to 1 if you have the `flistea' function. */
/* #undef HAVE_FLISTEA */

/* Define to 1 if you have the `flistxattr' function. */
/* #undef HAVE_FLISTXATTR */

/* Define to 1 if you have the <float.h> header file. */
#define HAVE_FLOAT_H 1

/* Define to 1 if you have the <fnmatch.h> header file. */
#define HAVE_FNMATCH_H 1

/* Define to 1 if you have the `fopen64' function. */
/* #undef HAVE_FOPEN64 */

/* Whether the system has freeaddrinfo */
#define HAVE_FREEADDRINFO 1

/* Whether we have FreeBSD sunacl around */
/* #undef HAVE_FREEBSD_SUNACL_H */

/* Whether the system has freeifaddrs */
#define HAVE_FREEIFADDRS 1

/* Define to 1 if you have the `free_AP_REQ' function. */
/* #undef HAVE_FREE_AP_REQ */

/* Define to 1 if you have the `fremoveea' function. */
/* #undef HAVE_FREMOVEEA */

/* Define to 1 if you have the `fremovexattr' function. */
/* #undef HAVE_FREMOVEXATTR */

/* Whether statvfs.f_frsize exists */
#define HAVE_FRSIZE 1

/* Define to 1 if you have the `fseek64' function. */
/* #undef HAVE_FSEEK64 */

/* Define to 1 if you have the `fseeko' function. */
#define HAVE_FSEEKO 1

/* Define to 1 if you have the `fseeko64' function. */
/* #undef HAVE_FSEEKO64 */

/* Define to 1 if you have the `fsetea' function. */
/* #undef HAVE_FSETEA */

/* Define to 1 if you have the `fsetproplist' function. */
/* #undef HAVE_FSETPROPLIST */

/* Define to 1 if you have the `fsetxattr' function. */
/* #undef HAVE_FSETXATTR */

/* Whether statvfs.f_fsid is an integer */
#define HAVE_FSID_INT 1

/* Whether fstat64() is available */
#define HAVE_FSTAT64 1

/* Define to 1 if you have the `fsync' function. */
#define HAVE_FSYNC 1

/* Define to 1 if you have the `ftell64' function. */
/* #undef HAVE_FTELL64 */

/* Define to 1 if you have the `ftello64' function. */
/* #undef HAVE_FTELLO64 */

/* Define to 1 if you have the `ftruncate' function. */
#define HAVE_FTRUNCATE 1

/* Define to 1 if you have the `ftruncate64' function. */
/* #undef HAVE_FTRUNCATE64 */

/* Truncate extend */
/* #undef HAVE_FTRUNCATE_EXTEND */

/* whether we can compile with __attribute__((destructor)) */
#define HAVE_FUNCTION_ATTRIBUTE_DESTRUCTOR 1

/* Whether there is a __FUNCTION__ macro */
#define HAVE_FUNCTION_MACRO 1

/* Define to 1 if you have the `futimens' function. */
#define HAVE_FUTIMENS 1

/* Define to 1 if you have the `futimes' function. */
/* #undef HAVE_FUTIMES */

/* Whether the system has gai_strerror */
#define HAVE_GAI_STRERROR 1

/* Whether the system has getaddrinfo */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `getauthuid' function. */
/* #undef HAVE_GETAUTHUID */

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if you have the `getdents' function. */
/* #undef HAVE_GETDENTS */

/* Define to 1 if you have the `getdents64' function. */
/* #undef HAVE_GETDENTS64 */

/* Define to 1 if you have the `getdirentries' function. */
/* #undef HAVE_GETDIRENTRIES */

/* Define to 1 if you have the `getea' function. */
/* #undef HAVE_GETEA */

/* Define to 1 if you have the `getgrent' function. */
#define HAVE_GETGRENT 1

/* Define to 1 if you have the `getgrent_r' function. */
/* #undef HAVE_GETGRENT_R */

/* Whether getgrent_r() is available */
/* #undef HAVE_GETGRENT_R_DECL */

/* Define to 1 if you have the `getgrgid_r' function. */
#define HAVE_GETGRGID_R 1

/* Define to 1 if you have the `getgrnam' function. */
#define HAVE_GETGRNAM 1

/* Define to 1 if you have the `getgrnam_r' function. */
#define HAVE_GETGRNAM_R 1

/* Define to 1 if you have the `getgrouplist' function. */
#define HAVE_GETGROUPLIST 1

/* Define to 1 if you have the `getgrset' function. */
/* #undef HAVE_GETGRSET */

/* Whether the system has gethostbyname() */
#define HAVE_GETHOSTBYNAME 1

/* Whether the system has getifaddrs */
#define HAVE_GETIFADDRS 1

/* Define to 1 if you have the `getmntent' function. */
/* #undef HAVE_GETMNTENT */

/* Whether the system has getnameinfo */
#define HAVE_GETNAMEINFO 1

/* Define to 1 if you have the `getnetgrent' function. */
/* #undef HAVE_GETNETGRENT */

/* If getnetgrent prototype is defined */
#define HAVE_GETNETGRENT_PROTOTYPE 1

/* Define to 1 if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Whether we have getpeereid to get socket credentials */
#define HAVE_GETPEEREID 1

/* Define to 1 if you have the `getpgrp' function. */
#define HAVE_GETPGRP 1

/* Define to 1 if you have the `getproplist' function. */
/* #undef HAVE_GETPROPLIST */

/* Whether getprpwnam is available */
/* #undef HAVE_GETPRPWNAM */

/* Define to 1 if you have the `getpwanam' function. */
/* #undef HAVE_GETPWANAM */

/* Define to 1 if you have the `getpwent_r' function. */
#define HAVE_GETPWENT_R 1

/* Whether getpwent_r() is available */
#define HAVE_GETPWENT_R_DECL 1

/* Define to 1 if you have the `getpwnam_r' function. */
#define HAVE_GETPWNAM_R 1

/* Define to 1 if you have the `getpwuid_r' function. */
#define HAVE_GETPWUID_R 1

/* Define to 1 if you have the `getrlimit' function. */
#define HAVE_GETRLIMIT 1

/* Whether getspnam is available */
#define HAVE_GETSPNAM 1

/* Define to 1 if you have the `gettext' function. */
/* #undef HAVE_GETTEXT */

/* Whether gettimeofday() is available */
#define HAVE_GETTIMEOFDAY_TZ 1

/* Define to 1 if you have the `getutmpx' function. */
/* #undef HAVE_GETUTMPX */

/* Define to 1 if you have the `getutxent' function. */
/* #undef HAVE_GETUTXENT */

/* Define to 1 if you have the `getxattr' function. */
/* #undef HAVE_GETXATTR */

/* Define to 1 if you have the `get_current_dir_name' function. */
/* #undef HAVE_GET_CURRENT_DIR_NAME */

/* Define to 1 if you have the `get_proplist_entry' function. */
/* #undef HAVE_GET_PROPLIST_ENTRY */

/* What header to include for iconv() function: giconv.h */
/* #undef HAVE_GICONV */

/* Define to 1 if you have the `glob' function. */
#define HAVE_GLOB 1

/* Define to 1 if you have the <glob.h> header file. */
#define HAVE_GLOB_H 1

/* Whether GPFS GPL headers are available */
/* #undef HAVE_GPFS */

/* Define to 1 if you have the <gpfs_gpl.h> header file. */
/* #undef HAVE_GPFS_GPL_H */

/* Define to 1 if you have the `grantpt' function. */
#define HAVE_GRANTPT 1

/* Define to 1 if you have the <grp.h> header file. */
#define HAVE_GRP_H 1

/* Whether GSSAPI is available */
/* #undef HAVE_GSSAPI */

/* Define to 1 if you have the <gssapi/gssapi_ext.h> header file. */
/* #undef HAVE_GSSAPI_GSSAPI_EXT_H */

/* Define to 1 if you have the <gssapi/gssapi_generic.h> header file. */
/* #undef HAVE_GSSAPI_GSSAPI_GENERIC_H */

/* Define to 1 if you have the <gssapi/gssapi.h> header file. */
/* #undef HAVE_GSSAPI_GSSAPI_H */

/* Define to 1 if you have the <gssapi.h> header file. */
/* #undef HAVE_GSSAPI_H */

/* Define to 1 if you have the `gss_display_status' function. */
/* #undef HAVE_GSS_DISPLAY_STATUS */

/* Define to 1 if you have the `gss_get_name_attribute' function. */
/* #undef HAVE_GSS_GET_NAME_ATTRIBUTE */

/* Define to 1 if you have the `gss_wrap_iov' function. */
/* #undef HAVE_GSS_WRAP_IOV */

/* Define to 1 if you have the <history.h> header file. */
/* #undef HAVE_HISTORY_H */

/* Do we have history_list? */
/* #undef HAVE_HISTORY_LIST */

/* Whether HPUX ACLs are available */
/* #undef HAVE_HPUX_ACLS */

/* Define to 1 if you have the `hstrerror' function. */
#define HAVE_HSTRERROR 1

/* Define to 1 if you have the `httpConnect' function. */
/* #undef HAVE_HTTPCONNECT */

/* Define to 1 if you have the `httpConnectEncrypt' function. */
/* #undef HAVE_HTTPCONNECTENCRYPT */

/* What header to include for iconv() function: iconv.h */
#define HAVE_ICONV 1

/* Whether iface AIX is available */
/* #undef HAVE_IFACE_AIX */

/* Whether iface getifaddrs is available */
/* #undef HAVE_IFACE_GETIFADDRS */

/* Whether iface ifconf is available */
/* #undef HAVE_IFACE_IFCONF */

/* Whether iface ifreq is available */
/* #undef HAVE_IFACE_IFREQ */

/* Define to 1 if you have the <ifaddrs.h> header file. */
#define HAVE_IFADDRS_H 1

/* Whether the system has if_nametoindex() */
/* #undef HAVE_IF_NAMETOINDEX */

/* Whether the compiler supports immediate structures */
#define HAVE_IMMEDIATE_STRUCTURES 1

/* Define to 1 if you have the `inet_aton' function. */
#define HAVE_INET_ATON 1

/* Define to 1 if you have the `inet_ntoa' function. */
#define HAVE_INET_NTOA 1

/* Define to 1 if you have the `inet_ntop' function. */
#define HAVE_INET_NTOP 1

/* Define to 1 if you have the `inet_pton' function. */
#define HAVE_INET_PTON 1

/* Define to 1 if you have the `initgroups' function. */
#define HAVE_INITGROUPS 1

/* Define to 1 if you have the `initialize_krb5_error_table' function. */
/* #undef HAVE_INITIALIZE_KRB5_ERROR_TABLE */

/* Define to 1 if you have the `innetgr' function. */
/* #undef HAVE_INNETGR */

/* Whether the 'ino64_t' type is available */
/* #undef HAVE_INO64_T */

/* Whether kernel or sys has inotify support */
#define HAVE_INOTIFY 1

/* Define to 1 if you have the `inotify_init' function. */
#define HAVE_INOTIFY_INIT 1

/* Whether int16 typedef is included by rpc/rpc.h */
/* #undef HAVE_INT16_FROM_RPC_RPC_H */

/* Whether int32 typedef is included by rpc/rpc.h */
/* #undef HAVE_INT32_FROM_RPC_RPC_H */

/* Define to 1 if the system has the type `intptr_t'. */
#define HAVE_INTPTR_T 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Whether we have iPrint */
/* #undef HAVE_IPRINT */

/* Whether the system has IPv6 support */
#define HAVE_IPV6 1

/* Whether IRIX ACLs are available */
/* #undef HAVE_IRIX_ACLS */

/* Define to 1 if you have the `isatty' function. */
#define HAVE_ISATTY 1

/* Whether kernel notifies changes */
/* #undef HAVE_KERNEL_CHANGE_NOTIFY */

/* Whether IRIX kernel oplock type definitions are available */
/* #undef HAVE_KERNEL_OPLOCKS_IRIX */

/* Whether to use linux kernel oplocks */
/* #undef HAVE_KERNEL_OPLOCKS_LINUX */

/* Whether the kernel supports share modes */
/* #undef HAVE_KERNEL_SHARE_MODES */

/* Whether to have KRB5 support */
/* #undef HAVE_KRB5 */

/* Whether the type krb5_addresses type exists */
/* #undef HAVE_KRB5_ADDRESSES */

/* Define to 1 if you have the `krb5_auth_con_setkey' function. */
/* #undef HAVE_KRB5_AUTH_CON_SETKEY */

/* Define to 1 if you have the `krb5_auth_con_setuseruserkey' function. */
/* #undef HAVE_KRB5_AUTH_CON_SETUSERUSERKEY */

/* Define to 1 if you have the `krb5_auth_con_set_req_cksumtype' function. */
/* #undef HAVE_KRB5_AUTH_CON_SET_REQ_CKSUMTYPE */

/* Whether the type krb5_crypto exists */
/* #undef HAVE_KRB5_CRYPTO */

/* Define to 1 if you have the `krb5_crypto_destroy' function. */
/* #undef HAVE_KRB5_CRYPTO_DESTROY */

/* Define to 1 if you have the `krb5_crypto_init' function. */
/* #undef HAVE_KRB5_CRYPTO_INIT */

/* Define to 1 if you have the `krb5_c_enctype_compare' function. */
/* #undef HAVE_KRB5_C_ENCTYPE_COMPARE */

/* Define to 1 if you have the `krb5_c_verify_checksum' function. */
/* #undef HAVE_KRB5_C_VERIFY_CHECKSUM */

/* Define to 1 if you have the `krb5_decode_ap_req' function. */
/* #undef HAVE_KRB5_DECODE_AP_REQ */

/* Whether to use deprecated krb5 interfaces */
/* #undef HAVE_KRB5_DEPRECATED_WITH_IDENTIFIER */

/* Whether the type krb5_encrypt_block exists */
/* #undef HAVE_KRB5_ENCRYPT_BLOCK */

/* Define to 1 if you have the `krb5_encrypt_data' function. */
/* #undef HAVE_KRB5_ENCRYPT_DATA */

/* Define to 1 if you have the `krb5_enctypes_compatible_keys' function. */
/* #undef HAVE_KRB5_ENCTYPES_COMPATIBLE_KEYS */

/* Define to 1 if you have the `krb5_enctype_to_string' function. */
/* #undef HAVE_KRB5_ENCTYPE_TO_STRING */

/* whether krb5_enctype_to_string takes krb5_context argument */
/* #undef HAVE_KRB5_ENCTYPE_TO_STRING_WITH_KRB5_CONTEXT_ARG */

/* whether krb5_enctype_to_string takes size_t argument */
/* #undef HAVE_KRB5_ENCTYPE_TO_STRING_WITH_SIZE_T_ARG */

/* Define to 1 if you have the `krb5_free_data_contents' function. */
/* #undef HAVE_KRB5_FREE_DATA_CONTENTS */

/* Define to 1 if you have the `krb5_free_error_contents' function. */
/* #undef HAVE_KRB5_FREE_ERROR_CONTENTS */

/* Define to 1 if you have the `krb5_free_host_realm' function. */
/* #undef HAVE_KRB5_FREE_HOST_REALM */

/* Define to 1 if you have the `krb5_free_keytab_entry_contents' function. */
/* #undef HAVE_KRB5_FREE_KEYTAB_ENTRY_CONTENTS */

/* Define to 1 if you have the `krb5_free_unparsed_name' function. */
/* #undef HAVE_KRB5_FREE_UNPARSED_NAME */

/* Define to 1 if you have the `krb5_fwd_tgt_creds' function. */
/* #undef HAVE_KRB5_FWD_TGT_CREDS */

/* Define to 1 if you have the `krb5_get_credentials_for_user' function. */
/* #undef HAVE_KRB5_GET_CREDENTIALS_FOR_USER */

/* Define to 1 if you have the `krb5_get_creds' function. */
/* #undef HAVE_KRB5_GET_CREDS */

/* Define to 1 if you have the `krb5_get_creds_opt_alloc' function. */
/* #undef HAVE_KRB5_GET_CREDS_OPT_ALLOC */

/* Define to 1 if you have the `krb5_get_creds_opt_set_impersonate' function.
   */
/* #undef HAVE_KRB5_GET_CREDS_OPT_SET_IMPERSONATE */

/* Define to 1 if you have the `krb5_get_default_in_tkt_etypes' function. */
/* #undef HAVE_KRB5_GET_DEFAULT_IN_TKT_ETYPES */

/* Define to 1 if you have the `krb5_get_host_realm' function. */
/* #undef HAVE_KRB5_GET_HOST_REALM */

/* Define to 1 if you have the `krb5_get_init_creds_opt_alloc' function. */
/* #undef HAVE_KRB5_GET_INIT_CREDS_OPT_ALLOC */

/* Define to 1 if you have the `krb5_get_init_creds_opt_free' function. */
/* #undef HAVE_KRB5_GET_INIT_CREDS_OPT_FREE */

/* Define to 1 if you have the `krb5_get_init_creds_opt_get_error' function.
   */
/* #undef HAVE_KRB5_GET_INIT_CREDS_OPT_GET_ERROR */

/* Define to 1 if you have the `krb5_get_init_creds_opt_set_pac_request'
   function. */
/* #undef HAVE_KRB5_GET_INIT_CREDS_OPT_SET_PAC_REQUEST */

/* Define to 1 if you have the `krb5_get_kdc_cred' function. */
/* #undef HAVE_KRB5_GET_KDC_CRED */

/* Define to 1 if you have the `krb5_get_permitted_enctypes' function. */
/* #undef HAVE_KRB5_GET_PERMITTED_ENCTYPES */

/* Define to 1 if you have the `krb5_get_pw_salt' function. */
/* #undef HAVE_KRB5_GET_PW_SALT */

/* Define to 1 if you have the `krb5_get_renewed_creds' function. */
/* #undef HAVE_KRB5_GET_RENEWED_CREDS */

/* Define to 1 if you have the <krb5.h> header file. */
/* #undef HAVE_KRB5_H */

/* Whether the krb5_creds struct has a keyblock property */
/* #undef HAVE_KRB5_KEYBLOCK_IN_CREDS */

/* Whether the krb5_keyblock struct has a keyvalue property */
/* #undef HAVE_KRB5_KEYBLOCK_KEYVALUE */

/* Whether krb5_keytab_entry has key member */
/* #undef HAVE_KRB5_KEYTAB_ENTRY_KEY */

/* Whether krb5_keytab_entry has keyblock member */
/* #undef HAVE_KRB5_KEYTAB_ENTRY_KEYBLOCK */

/* Whether KRB5_KEYUSAGE_APP_DATA_CKSUM is available */
/* #undef HAVE_KRB5_KEYUSAGE_APP_DATA_CKSUM */

/* Define to 1 if you have the `krb5_krbhst_get_addrinfo' function. */
/* #undef HAVE_KRB5_KRBHST_GET_ADDRINFO */

/* Define to 1 if you have the `krb5_krbhst_init' function. */
/* #undef HAVE_KRB5_KRBHST_INIT */

/* Define to 1 if you have the `krb5_kt_compare' function. */
/* #undef HAVE_KRB5_KT_COMPARE */

/* Define to 1 if you have the `krb5_kt_free_entry' function. */
/* #undef HAVE_KRB5_KT_FREE_ENTRY */

/* Whether KRB5_KU_OTHER_CKSUM is available */
/* #undef HAVE_KRB5_KU_OTHER_CKSUM */

/* Define to 1 if you have the <krb5/locate_plugin.h> header file. */
/* #undef HAVE_KRB5_LOCATE_PLUGIN_H */

/* Define to 1 if you have the `krb5_mk_req_extended' function. */
/* #undef HAVE_KRB5_MK_REQ_EXTENDED */

/* Define to 1 if you have the `krb5_parse_name_norealm' function. */
/* #undef HAVE_KRB5_PARSE_NAME_NOREALM */

/* Define to 1 if you have the `krb5_principal2salt' function. */
/* #undef HAVE_KRB5_PRINCIPAL2SALT */

/* Define to 1 if you have the `krb5_principal_compare_any_realm' function. */
/* #undef HAVE_KRB5_PRINCIPAL_COMPARE_ANY_REALM */

/* Define to 1 if you have the `krb5_principal_get_comp_string' function. */
/* #undef HAVE_KRB5_PRINCIPAL_GET_COMP_STRING */

/* Whether the function krb5_principal_get_realm is defined */
/* #undef HAVE_KRB5_PRINCIPAL_GET_REALM */

/* Whether krb5_princ_component is available */
/* #undef HAVE_KRB5_PRINC_COMPONENT */

/* Whether the macro krb5_princ_realm is defined */
/* #undef HAVE_KRB5_PRINC_REALM */

/* Define to 1 if you have the `krb5_princ_size' function. */
/* #undef HAVE_KRB5_PRINC_SIZE */

/* Whether the type krb5_realm exists */
/* #undef HAVE_KRB5_REALM_TYPE */

/* Whether the krb5_creds struct has a session property */
/* #undef HAVE_KRB5_SESSION_IN_CREDS */

/* Define to 1 if you have the `krb5_set_default_in_tkt_etypes' function. */
/* #undef HAVE_KRB5_SET_DEFAULT_IN_TKT_ETYPES */

/* Define to 1 if you have the `krb5_set_default_tgs_enctypes' function. */
/* #undef HAVE_KRB5_SET_DEFAULT_TGS_ENCTYPES */

/* Define to 1 if you have the `krb5_set_default_tgs_ktypes' function. */
/* #undef HAVE_KRB5_SET_DEFAULT_TGS_KTYPES */

/* Define to 1 if you have the `krb5_set_real_time' function. */
/* #undef HAVE_KRB5_SET_REAL_TIME */

/* Define to 1 if you have the `krb5_string_to_key' function. */
/* #undef HAVE_KRB5_STRING_TO_KEY */

/* Define to 1 if you have the `krb5_string_to_key_salt' function. */
/* #undef HAVE_KRB5_STRING_TO_KEY_SALT */

/* Whether the krb5_ticket struct has a enc_part2 property */
/* #undef HAVE_KRB5_TKT_ENC_PART2 */

/* Define to 1 if you have the `krb5_use_enctype' function. */
/* #undef HAVE_KRB5_USE_ENCTYPE */

/* Define to 1 if you have the `krb5_verify_checksum' function. */
/* #undef HAVE_KRB5_VERIFY_CHECKSUM */

/* Whether the KV5M_KEYTAB option is available */
/* #undef HAVE_KV5M_KEYTAB */

/* Define to 1 if you have the <langinfo.h> header file. */
/* #undef HAVE_LANGINFO_H */

/* Define to 1 if you have the <lastlog.h> header file. */
/* #undef HAVE_LASTLOG_H */

/* Define to 1 if you have the <lber.h> header file. */
/* #undef HAVE_LBER_H */

/* Support for LDAP/LBER logging interception */
/* #undef HAVE_LBER_LOG_PRINT_FN */

/* Define to 1 if you have the `lchown' function. */
#define HAVE_LCHOWN 1

/* Whether ldap is available */
/* #undef HAVE_LDAP */

/* Define to 1 if you have the `ldap_add_result_entry' function. */
/* #undef HAVE_LDAP_ADD_RESULT_ENTRY */

/* Define to 1 if you have the <ldap.h> header file. */
/* #undef HAVE_LDAP_H */

/* Define to 1 if you have the `ldap_init' function. */
/* #undef HAVE_LDAP_INIT */

/* Define to 1 if you have the `ldap_initialize' function. */
/* #undef HAVE_LDAP_INITIALIZE */

/* Support for SASL wrapping */
/* #undef HAVE_LDAP_SASL_WRAPPING */

/* Define to 1 if you have the `ldap_set_rebind_proc' function. */
/* #undef HAVE_LDAP_SET_REBIND_PROC */

/* Define to 1 if you have the `lgetea' function. */
/* #undef HAVE_LGETEA */

/* Define to 1 if you have the `lgetxattr' function. */
/* #undef HAVE_LGETXATTR */

/* Define to 1 if you have the `asn1' library (-lasn1). */
/* #undef HAVE_LIBASN1 */

/* Define to 1 if you have the `com_err' library (-lcom_err). */
/* #undef HAVE_LIBCOM_ERR */

/* Define to 1 if you have the `crypto' library (-lcrypto). */
/* #undef HAVE_LIBCRYPTO */

/* Define to 1 if you have the `cups' library (-lcups). */
/* #undef HAVE_LIBCUPS */

/* Define to 1 if you have the `dns_sd' library (-ldns_sd). */
/* #undef HAVE_LIBDNS_SD */

/* Define to 1 if you have the `exc' library (-lexc). */
/* #undef HAVE_LIBEXC */

/* Define to 1 if you have the <libexc.h> header file. */
/* #undef HAVE_LIBEXC_H */

/* Define to 1 if you have the `fam' library (-lfam). */
/* #undef HAVE_LIBFAM */

/* Define to 1 if you have the `gssapi' library (-lgssapi). */
/* #undef HAVE_LIBGSSAPI */

/* Define to 1 if you have the `gssapi_krb5' library (-lgssapi_krb5). */
/* #undef HAVE_LIBGSSAPI_KRB5 */

/* Define to 1 if you have the `inet' library (-linet). */
/* #undef HAVE_LIBINET */

/* Define to 1 if you have the <libintl.h> header file. */
#define HAVE_LIBINTL_H 1

/* Define to 1 if you have the `ipv6' library (-lipv6). */
/* #undef HAVE_LIBIPV6 */

/* Define to 1 if you have the `k5crypto' library (-lk5crypto). */
/* #undef HAVE_LIBK5CRYPTO */

/* Define to 1 if you have the `krb5' library (-lkrb5). */
/* #undef HAVE_LIBKRB5 */

/* Define to 1 if you have the `lber' library (-llber). */
/* #undef HAVE_LIBLBER */

/* Define to 1 if you have the `ldap' library (-lldap). */
/* #undef HAVE_LIBLDAP */

/* Whether libmd5 conformant to rfc1321 is available. */
/* #undef HAVE_LIBMD5 */

/* Define to 1 if you have the `nscd' library (-lnscd). */
/* #undef HAVE_LIBNSCD */

/* Define to 1 if you have the `nsl' library (-lnsl). */
/* #undef HAVE_LIBNSL */

/* Define to 1 if you have the `nsl_s' library (-lnsl_s). */
/* #undef HAVE_LIBNSL_S */

/* Whether libpam is available */
#define HAVE_LIBPAM 1

/* Whether the system has readline */
#define HAVE_LIBREADLINE 1

/* Define to 1 if you have the `resolv' library (-lresolv). */
/* #undef HAVE_LIBRESOLV */

/* Define to 1 if you have the `roken' library (-lroken). */
/* #undef HAVE_LIBROKEN */

/* Define to 1 if you have the `rt' library (-lrt). */
/* #undef HAVE_LIBRT */

/* Define to 1 if you have the `sendfile' library (-lsendfile). */
/* #undef HAVE_LIBSENDFILE */

/* Define to 1 if you have the `socket' library (-lsocket). */
#define HAVE_LIBSOCKET 1

/* Whether libunwind is available */
/* #undef HAVE_LIBUNWIND */

/* Define to 1 if you have the <libunwind.h> header file. */
/* #undef HAVE_LIBUNWIND_H */

/* Whether libunwind-ptrace.a is available. */
/* #undef HAVE_LIBUNWIND_PTRACE */

/* Define to 1 if you have the <libunwind-ptrace.h> header file. */
/* #undef HAVE_LIBUNWIND_PTRACE_H */

/* Define to 1 if you have the `z' library (-lz). */
#define HAVE_LIBZ 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the `link' function. */
#define HAVE_LINK 1

/* Define to 1 if you have the <linux/dqblk_xfs.h> header file. */
/* #undef HAVE_LINUX_DQBLK_XFS_H */

/* Whether the Linux 'fallocate' function is available */
/* #undef HAVE_LINUX_FALLOCATE */

/* Whether the Linux 'fallocate64' function is available */
/* #undef HAVE_LINUX_FALLOCATE64 */

/* Define to 1 if you have the <linux/falloc.h> header file. */
/* #undef HAVE_LINUX_FALLOC_H */

/* Define to 1 if you have the <linux/inotify.h> header file. */
/* #undef HAVE_LINUX_INOTIFY_H */

/* Whether the system has IPV6_V6ONLY in linux/in6.h */
/* #undef HAVE_LINUX_IPV6_V6ONLY_26 */

/* Define to 1 if you have the <linux/netlink.h> header file. */
/* #undef HAVE_LINUX_NETLINK_H */

/* Whether the Linux ptrace(2) interface is available. */
/* #undef HAVE_LINUX_PTRACE */

/* Whether Linux readahead is available */
/* #undef HAVE_LINUX_READAHEAD */

/* Define to 1 if you have the <linux/rtnetlink.h> header file. */
/* #undef HAVE_LINUX_RTNETLINK_H */

/* Whether Linux splice is available */
/* #undef HAVE_LINUX_SPLICE */

/* Define to 1 if you have the <linux/types.h> header file. */
/* #undef HAVE_LINUX_TYPES_H */

/* Whether Linux xfs quota support is available */
/* #undef HAVE_LINUX_XFS_QUOTAS */

/* Define to 1 if you have the `listea' function. */
/* #undef HAVE_LISTEA */

/* Define to 1 if you have the `listxattr' function. */
/* #undef HAVE_LISTXATTR */

/* Define to 1 if you have the `llistea' function. */
/* #undef HAVE_LLISTEA */

/* Define to 1 if you have the `llistxattr' function. */
/* #undef HAVE_LLISTXATTR */

/* Define to 1 if you have the `llseek' function. */
/* #undef HAVE_LLSEEK */

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Whether the host supports long long's */
/* #undef HAVE_LONGLONG */

/* Define to 1 if the system has the type `long long'. */
#define HAVE_LONG_LONG 1

/* Define to 1 if you have the `lremoveea' function. */
/* #undef HAVE_LREMOVEEA */

/* Define to 1 if you have the `lremovexattr' function. */
/* #undef HAVE_LREMOVEXATTR */

/* Define to 1 if you have the `lseek64' function. */
/* #undef HAVE_LSEEK64 */

/* Define to 1 if you have the `lsetea' function. */
/* #undef HAVE_LSETEA */

/* Define to 1 if you have the `lsetxattr' function. */
/* #undef HAVE_LSETXATTR */

/* Define to 1 if you have the `lstat' function. */
#define HAVE_LSTAT 1

/* Define to 1 if you have the `lstat64' function. */
#define HAVE_LSTAT64 Whether lstat64() is available

/* Define to 1 if you have the `lutimes' function. */
/* #undef HAVE_LUTIMES */

/* Whether the krb5_address struct has a magic property */
/* #undef HAVE_MAGIC_IN_KRB5_ADDRESS */

/* Whether the macro for makedev is available */
/* #undef HAVE_MAKEDEV */

/* Define to 1 if you have the <md5.h> header file. */
/* #undef HAVE_MD5_H */

/* Define to 1 if you have the `memalign' function. */
#define HAVE_MEMALIGN 1

/* Define to 1 if you have the `memcpy' function. */
#define HAVE_MEMCPY 1

/* Define to 1 if you have the `memmem' function. */
/* #undef HAVE_MEMMEM */

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Whether memset() is available */
#define HAVE_MEMSET 1

/* Define if target mkdir supports mode option */
#define HAVE_MKDIR_MODE 1

/* Define to 1 if you have the `mkdtemp' function. */
#define HAVE_MKDTEMP 1

/* Define to 1 if you have the `mknod' function. */
#define HAVE_MKNOD 1

/* Define to 1 if you have the `mknod64' function. */
/* #undef HAVE_MKNOD64 */

/* Define to 1 if you have the `mktime' function. */
#define HAVE_MKTIME 1

/* Define to 1 if you have the `mlock' function. */
#define HAVE_MLOCK 1

/* Define to 1 if you have the `mlockall' function. */
#define HAVE_MLOCKALL 1

/* Define to 1 if you have the `mmap' function. */
#define HAVE_MMAP 1

/* Define to 1 if you have the <mntent.h> header file. */
/* #undef HAVE_MNTENT_H */

/* If we can use msg_acctrights for passing file descriptors */
/* #undef HAVE_MSGHDR_MSG_ACCTRIGHTS */

/* If we can use msg_control for passing file descriptors */
#define HAVE_MSGHDR_MSG_CONTROL 1

/* Define to 1 if you have the `munlock' function. */
#define HAVE_MUNLOCK 1

/* Define to 1 if you have the `munlockall' function. */
#define HAVE_MUNLOCKALL 1

/* Define to 1 if you have the `nanosleep' function. */
#define HAVE_NANOSLEEP 1

/* Whether to use native iconv */
#define HAVE_NATIVE_ICONV 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netgroup.h> header file. */
/* #undef HAVE_NETGROUP_H */

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <netinet/in_ip.h> header file. */
/* #undef HAVE_NETINET_IN_IP_H */

/* Define to 1 if you have the <netinet/in_systm.h> header file. */
#define HAVE_NETINET_IN_SYSTM_H 1

/* Define to 1 if you have the <netinet/ip.h> header file. */
#define HAVE_NETINET_IP_H 1

/* Define to 1 if you have the <netinet/tcp.h> header file. */
#define HAVE_NETINET_TCP_H 1

/* usability of net/if.h */
#define HAVE_NET_IF_H 1

/* Do we have rl_completion_matches? */
#define HAVE_NEW_LIBREADLINE 1

/* Whether nfs quota support is available */
/* #undef HAVE_NFS_QUOTAS */

/* Define to 1 if you have the `nl_langinfo' function. */
/* #undef HAVE_NL_LANGINFO */

/* Whether no ACLs support is available */
/* #undef HAVE_NO_ACLS */

/* Whether no asynchronous io support is available */
#define HAVE_NO_AIO 1

/* Define to 1 if you have the `nscd_flush_cache' function. */
/* #undef HAVE_NSCD_FLUSH_CACHE */

/* Define to 1 if you have the <nsswitch.h> header file. */
#define HAVE_NSSWITCH_H 1

/* Define to 1 if you have the <nss_common.h> header file. */
/* #undef HAVE_NSS_COMMON_H */

/* Define to 1 if you have the <nss.h> header file. */
/* #undef HAVE_NSS_H */

/* Defined if union nss_XbyY_key has ipnode field */
/* #undef HAVE_NSS_XBYY_KEY_IPNODE */

/* Define to 1 if you have the <ns_api.h> header file. */
/* #undef HAVE_NS_API_H */

/* Whether off64_t is available */
/* #undef HAVE_OFF64_T */

/* Whether building on Isilon OneFS */
/* #undef HAVE_ONEFS */

/* Define to 1 if you have the `open64' function. */
/* #undef HAVE_OPEN64 */

/* Define to 1 if you have the `opendir64' function. */
/* #undef HAVE_OPENDIR64 */

/* Whether the open(2) accepts O_DIRECT */
/* #undef HAVE_OPEN_O_DIRECT */

/* Define to 1 if you have the `pam_get_data' function. */
#define HAVE_PAM_GET_DATA 1

/* Define to 1 if you have the <pam/pam_appl.h> header file. */
/* #undef HAVE_PAM_PAM_APPL_H */

/* Define to 1 if you have the <pam/pam_ext.h> header file. */
/* #undef HAVE_PAM_PAM_EXT_H */

/* Define to 1 if you have the <pam/pam_modules.h> header file. */
/* #undef HAVE_PAM_PAM_MODULES_H */

/* Define to 1 if PAM_RADIO_TYPE is available */
/* #undef HAVE_PAM_RADIO_TYPE */

/* Define to 1 if PAM_RHOST is available */
#define HAVE_PAM_RHOST 1

/* Define to 1 if PAM_TTY is available */
#define HAVE_PAM_TTY 1

/* Define to 1 if you have the `pam_vsyslog' function. */
/* #undef HAVE_PAM_VSYSLOG */

/* Define to 1 if you have the <pam/_pam_macros.h> header file. */
/* #undef HAVE_PAM__PAM_MACROS_H */

/* Defined if struct passwd has pw_age field */
#define HAVE_PASSWD_PW_AGE 1

/* Defined if struct passwd has pw_comment field */
#define HAVE_PASSWD_PW_COMMENT 1

/* Define to 1 if you have the `pathconf' function. */
#define HAVE_PATHCONF 1

/* Whether we can use SO_PEERCRED to get socket credentials */
/* #undef HAVE_PEERCRED */

/* Define to 1 if you have the `pipe' function. */
#define HAVE_PIPE 1

/* Define to 1 if you have the `poll' function. */
#define HAVE_POLL 1

/* Define to 1 if you have the <poll.h> header file. */
#define HAVE_POLL_H 1

/* Whether POSIX ACLs are available */
#define HAVE_POSIX_ACLS 1

/* Whether POSIX capabilities are available */
/* #undef HAVE_POSIX_CAPABILITIES */

/* Whether posix_fadvise is available */
#define HAVE_POSIX_FADVISE 1

/* Define to 1 if you have the `posix_fallocate' function. */
#define HAVE_POSIX_FALLOCATE 1

/* Define to 1 if you have the `posix_fallocate64' function. */
/* #undef HAVE_POSIX_FALLOCATE64 */

/* Define to 1 if you have the `posix_memalign' function. */
#define HAVE_POSIX_MEMALIGN 1

/* Define to 1 if you have the `posix_openpt' function. */
#define HAVE_POSIX_OPENPT 1

/* Whether prctl is available */
#define HAVE_PRCTL 1

/* Define to 1 if you have the `pread' function. */
#define HAVE_PREAD 1

/* Define to 1 if you have the `pread64' function. */
/* #undef HAVE_PREAD64 */

/* Whether pread() is available */
#define HAVE_PREAD_DECL 1

/* Define to 1 if you have the `printf' function. */
#define HAVE_PRINTF 1

/* Do we have pthreads around? */
#define HAVE_PTHREAD 1

/* Define to 1 if you have the <pthread.h> header file. */
#define HAVE_PTHREAD_H 1

/* Define to 1 if the system has the type `ptrdiff_t'. */
#define HAVE_PTRDIFF_T 1

/* Whether putprpwnam is available */
/* #undef HAVE_PUTPRPWNAM */

/* Define to 1 if you have the `pututline' function. */
#define HAVE_PUTUTLINE 1

/* Define to 1 if you have the `pututxline' function. */
/* #undef HAVE_PUTUTXLINE */

/* Define to 1 if you have the <pwd.h> header file. */
#define HAVE_PWD_H 1

/* Define to 1 if you have the `pwrite' function. */
#define HAVE_PWRITE 1

/* Define to 1 if you have the `pwrite64' function. */
/* #undef HAVE_PWRITE64 */

/* Whether pwrite() is available */
#define HAVE_PWRITE_DECL 1

/* Whether CRAY int quotactl (char *spec, int request, char *arg); is
   available */
/* #undef HAVE_QUOTACTL_3 */

/* Whether long quotactl(int cmd, char *special, qid_t id, caddr_t addr) is
   available */
/* #undef HAVE_QUOTACTL_4A */

/* Whether int quotactl(const char *path, int cmd, int id, char *addr) is
   available */
/* #undef HAVE_QUOTACTL_4B */

/* Whether Linux quota support is available */
/* #undef HAVE_QUOTACTL_LINUX */

/* Define to 1 if you have the `rand' function. */
#define HAVE_RAND 1

/* Define to 1 if you have the `random' function. */
#define HAVE_RANDOM 1

/* Define to 1 if you have the `rdchk' function. */
#define HAVE_RDCHK 1

/* Whether readahead() is available */
/* #undef HAVE_READAHEAD_DECL */

/* Define to 1 if you have the `readdir64' function. */
/* #undef HAVE_READDIR64 */

/* Define to 1 if you have the <readline.h> header file. */
/* #undef HAVE_READLINE_H */

/* Define to 1 if you have the <readline/history.h> header file. */
#define HAVE_READLINE_HISTORY_H 1

/* Define to 1 if you have the <readline/readline.h> header file. */
#define HAVE_READLINE_READLINE_H 1

/* Define to 1 if you have the `readlink' function. */
#define HAVE_READLINK 1

/* Define to 1 if you have the `realpath' function. */
#define HAVE_REALPATH 1

/* Define to 1 if you have the `removeea' function. */
/* #undef HAVE_REMOVEEA */

/* Define to 1 if you have the `removexattr' function. */
/* #undef HAVE_REMOVEXATTR */

/* Define to 1 if you have the `rename' function. */
#define HAVE_RENAME 1

/* Define to 1 if you have the `rewinddir64' function. */
/* #undef HAVE_REWINDDIR64 */

/* Define to 1 if you have the `roken_getaddrinfo_hostspec' function. */
/* #undef HAVE_ROKEN_GETADDRINFO_HOSTSPEC */

/* Define to 1 if you have the <rpcsvc/nis.h> header file. */
/* #undef HAVE_RPCSVC_NIS_H */

/* Define to 1 if you have the <rpcsvc/ypclnt.h> header file. */
/* #undef HAVE_RPCSVC_YPCLNT_H */

/* Define to 1 if you have the <rpcsvc/yp_prot.h> header file. */
/* #undef HAVE_RPCSVC_YP_PROT_H */

/* Whether there is a conflicting AUTH_ERROR define in rpc/rpc.h */
/* #undef HAVE_RPC_AUTH_ERROR_CONFLICT */

/* Define to 1 if you have the <rpc/nettype.h> header file. */
#define HAVE_RPC_NETTYPE_H 1

/* Define to 1 if you have the <rpc/rpc.h> header file. */
#define HAVE_RPC_RPC_H 1

/* Define to 1 if the system has the type `sa_family_t'. */
#define HAVE_SA_FAMILY_T 1

/* Whether mkstemp is secure */
/* #undef HAVE_SECURE_MKSTEMP */

/* Define to 1 if you have the <security/pam_appl.h> header file. */
#define HAVE_SECURITY_PAM_APPL_H 1

/* Define to 1 if you have the <security/pam_ext.h> header file. */
/* #undef HAVE_SECURITY_PAM_EXT_H */

/* Define to 1 if you have the <security/pam_modules.h> header file. */
#define HAVE_SECURITY_PAM_MODULES_H 1

/* Define to 1 if you have the <security/_pam_macros.h> header file. */
/* #undef HAVE_SECURITY__PAM_MACROS_H */

/* Define to 1 if you have the `seekdir64' function. */
/* #undef HAVE_SEEKDIR64 */

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Whether sendfile() is available */
/* #undef HAVE_SENDFILE */

/* Whether sendfile64() is available */
/* #undef HAVE_SENDFILE64 */

/* Whether sendfilev() is available */
/* #undef HAVE_SENDFILEV */

/* Whether sendfilev64() is available */
/* #undef HAVE_SENDFILEV64 */

/* Define to 1 if you have the `setbuffer' function. */
#define HAVE_SETBUFFER 1

/* Define to 1 if you have the `setea' function. */
/* #undef HAVE_SETEA */

/* Define to 1 if you have the `setegid' function. */
#define HAVE_SETEGID 1

/* Define to 1 if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Whether setenv() is available */
#define HAVE_SETENV_DECL 1

/* Define to 1 if you have the `seteuid' function. */
#define HAVE_SETEUID 1

/* Define to 1 if you have the `setgidx' function. */
/* #undef HAVE_SETGIDX */

/* Define to 1 if you have the `setgroups' function. */
#define HAVE_SETGROUPS 1

/* Define to 1 if you have the <setjmp.h> header file. */
#define HAVE_SETJMP_H 1

/* Define to 1 if you have the `setlinebuf' function. */
#define HAVE_SETLINEBUF 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the `setluid' function. */
/* #undef HAVE_SETLUID */

/* Define to 1 if you have the `setmntent' function. */
/* #undef HAVE_SETMNTENT */

/* Define to 1 if you have the `setnetgrent' function. */
/* #undef HAVE_SETNETGRENT */

/* If setnetgrent prototype is defined */
#define HAVE_SETNETGRENT_PROTOTYPE 1

/* Define to 1 if you have the `setpgid' function. */
#define HAVE_SETPGID 1

/* Define to 1 if you have the `setpriv' function. */
/* #undef HAVE_SETPRIV */

/* Define to 1 if you have the `setproplist' function. */
/* #undef HAVE_SETPROPLIST */

/* Whether the system has setresgid */
/* #undef HAVE_SETRESGID */

/* Whether setresgid() is available */
/* #undef HAVE_SETRESGID_DECL */

/* Whether the system has setresuid */
/* #undef HAVE_SETRESUID */

/* Whether setresuid() is available */
/* #undef HAVE_SETRESUID_DECL */

/* Define to 1 if you have the `setsid' function. */
#define HAVE_SETSID 1

/* Define to 1 if you have the `setuidx' function. */
/* #undef HAVE_SETUIDX */

/* Define to 1 if you have the `setxattr' function. */
/* #undef HAVE_SETXATTR */

/* Whether set_auth_parameters is available */
/* #undef HAVE_SET_AUTH_PARAMETERS */

/* Define to 1 if you have the <shadow.h> header file. */
#define HAVE_SHADOW_H 1

/* Define to 1 if you have the `shl_findsym' function. */
/* #undef HAVE_SHL_FINDSYM */

/* Define to 1 if you have the `shl_load' function. */
/* #undef HAVE_SHL_LOAD */

/* Define to 1 if you have the `shl_unload' function. */
/* #undef HAVE_SHL_UNLOAD */

/* Define to 1 if you have the `shmget' function. */
/* #undef HAVE_SHMGET */

/* Define to 1 if you have the `shm_open' function. */
#define HAVE_SHM_OPEN 1

/* whether krb5_mk_error takes 3 arguments MIT or 9 Heimdal */
/* #undef HAVE_SHORT_KRB5_MK_ERROR_INTERFACE */

/* Define to 1 if you have the `sigaction' function. */
#define HAVE_SIGACTION 1

/* Define to 1 if you have the `sigblock' function. */
#define HAVE_SIGBLOCK 1

/* Define to 1 if you have the `sigprocmask' function. */
#define HAVE_SIGPROCMASK 1

/* Define to 1 if you have the `sigset' function. */
/* #undef HAVE_SIGSET */

/* Whether we have the atomic_t variable type */
#define HAVE_SIG_ATOMIC_T_TYPE 1

/* Define to 1 if you have the `sizeof_proplist_entry' function. */
/* #undef HAVE_SIZEOF_PROPLIST_ENTRY */

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Whether struct sockaddr has a sa_len member */
#define HAVE_SOCKADDR_SA_LEN 1

/* Define to 1 if you have the `socketpair' function. */
#define HAVE_SOCKETPAIR 1

/* Define to 1 if the system has the type `socklen_t'. */
#define HAVE_SOCKLEN_T 1

/* Whether the sockaddr_in struct has a sin_len property */
#define HAVE_SOCK_SIN_LEN 1

/* Whether solaris ACLs are available */
/* #undef HAVE_SOLARIS_ACLS */

/* Whether splice() is available */
/* #undef HAVE_SPLICE_DECL */

/* Define to 1 if you have the `srand' function. */
#define HAVE_SRAND 1

/* Define to 1 if you have the `srandom' function. */
#define HAVE_SRANDOM 1

/* Defined if struct sockaddr_storage has ss_family field */
#define HAVE_SS_FAMILY 1

/* Define to 1 if you have the <standards.h> header file. */
/* #undef HAVE_STANDARDS_H */

/* Whether stat64() is available */
#define HAVE_STAT64 1

/* Whether statvfs.f_flag exists */
#define HAVE_STATVFS_F_FLAG 1

/* Whether statvfs.f_flags exists */
/* #undef HAVE_STATVFS_F_FLAGS */

/* whether there is DOS flags support in the stat struct */
/* #undef HAVE_STAT_DOS_FLAGS */

/* whether struct stat has sub-second timestamps */
#define HAVE_STAT_HIRES_TIMESTAMPS 1

/* Whether the stat struct has a st_blksize property */
#define HAVE_STAT_ST_BLKSIZE 1

/* Whether the stat struct has a st_block property */
#define HAVE_STAT_ST_BLOCKS 1

/* Whether the stat struct has a st_flags member */
/* #undef HAVE_STAT_ST_FLAGS */

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdbool.h> header file. */
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strcasestr' function. */
#define HAVE_STRCASESTR 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the `strerror_r' function. */
#define HAVE_STRERROR_R 1

/* Define to 1 if you have the `strftime' function. */
#define HAVE_STRFTIME 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlcat' function. */
#define HAVE_STRLCAT 1

/* Define to 1 if you have the `strlcpy' function. */
#define HAVE_STRLCPY 1

/* Define to 1 if you have the `strndup' function. */
/* #undef HAVE_STRNDUP */

/* Define to 1 if you have the `strnlen' function. */
#define HAVE_STRNLEN 1

/* Define to 1 if you have the <stropts.h> header file. */
/* #undef HAVE_STROPTS_H */

/* Define to 1 if you have the `strpbrk' function. */
#define HAVE_STRPBRK 1

/* Define to 1 if you have the `strsignal' function. */
#define HAVE_STRSIGNAL 1

/* Define to 1 if you have the `strtok_r' function. */
#define HAVE_STRTOK_R 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the `strtoll' function. */
#define HAVE_STRTOLL 1

/* Define to 1 if you have the `strtoq' function. */
/* #undef HAVE_STRTOQ */

/* Define to 1 if you have the `strtoull' function. */
#define HAVE_STRTOULL 1

/* Define to 1 if you have the `strtouq' function. */
/* #undef HAVE_STRTOUQ */

/* Define to 1 if the system has the type `struct addrinfo'. */
#define HAVE_STRUCT_ADDRINFO 1

/* ctdb ipv4 support */
/* #undef HAVE_STRUCT_CTDB_CONTROL_TCP */

/* ctdb ipv6 support */
/* #undef HAVE_STRUCT_CTDB_CONTROL_TCP_ADDR */

/* Whether the 'DIR64' abstract data type is available */
/* #undef HAVE_STRUCT_DIR64 */

/* Whether the 'dirent64' struct is available */
/* #undef HAVE_STRUCT_DIRENT64 */

/* Whether the flock64 struct is available */
/* #undef HAVE_STRUCT_FLOCK64 */

/* Whether struct ifaddrs is available */
#define HAVE_STRUCT_IFADDRS 1

/* Define to 1 if `method_attrlist' is a member of `struct secmethod_table'.
   */
/* #undef HAVE_STRUCT_SECMETHOD_TABLE_METHOD_ATTRLIST */

/* Define to 1 if `method_version' is a member of `struct secmethod_table'. */
/* #undef HAVE_STRUCT_SECMETHOD_TABLE_METHOD_VERSION */

/* Whether we have the struct sigevent */
#define HAVE_STRUCT_SIGEVENT 1

/* Define to 1 if `sigev_value.sigval_ptr' is a member of `struct sigevent'.
   */
/* #undef HAVE_STRUCT_SIGEVENT_SIGEV_VALUE_SIGVAL_PTR */

/* Define to 1 if `sigev_value.sival_ptr' is a member of `struct sigevent'. */
#define HAVE_STRUCT_SIGEVENT_SIGEV_VALUE_SIVAL_PTR 1

/* Define to 1 if the system has the type `struct sockaddr'. */
#define HAVE_STRUCT_SOCKADDR 1

/* Define to 1 if the system has the type `struct sockaddr_in6'. */
#define HAVE_STRUCT_SOCKADDR_IN6 1

/* Define to 1 if `sa_len' is a member of `struct sockaddr'. */
#define HAVE_STRUCT_SOCKADDR_SA_LEN 1

/* Define to 1 if the system has the type `struct sockaddr_storage'. */
#define HAVE_STRUCT_SOCKADDR_STORAGE 1

/* Define to 1 if `st_birthtime' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_BIRTHTIME */

/* Define to 1 if `st_birthtimensec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_BIRTHTIMENSEC */

/* Define to 1 if `st_birthtimespec.tv_nsec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_BIRTHTIMESPEC_TV_NSEC */

/* Define to 1 if `st_mtimensec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_MTIMENSEC */

/* Define to 1 if `st_mtimespec.tv_nsec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_MTIMESPEC_TV_NSEC */

/* Define to 1 if `st_mtime_n' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_MTIME_N */

/* Define to 1 if `st_mtim.tv_nsec' is a member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC 1

/* Define to 1 if `st_rdev' is a member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_RDEV 1

/* Define to 1 if `st_umtime' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_UMTIME */

/* Whether we have struct timespec */
#define HAVE_STRUCT_TIMESPEC 1

/* Define to 1 if you have the `strupr' function. */
#define HAVE_STRUPR 1

/* Define to 1 if your `struct stat' has `st_rdev'. Deprecated, use
   `HAVE_STRUCT_STAT_ST_RDEV' instead. */
#define HAVE_ST_RDEV 1

/* Define to 1 if you have the `symlink' function. */
#define HAVE_SYMLINK 1

/* Define to 1 if you have the <syscall.h> header file. */
/* #undef HAVE_SYSCALL_H */

/* Define to 1 if you have the `sysconf' function. */
#define HAVE_SYSCONF 1

/* Define to 1 if you have the `sysctlbyname' function. */
#define HAVE_SYSCTLBYNAME 1

/* Define to 1 if you have the `syslog' function. */
#define HAVE_SYSLOG 1

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 1

/* Define to 1 if you have the <sys/acl.h> header file. */
#define HAVE_SYS_ACL_H 1

/* Define to 1 if you have the <sys/attributes.h> header file. */
/* #undef HAVE_SYS_ATTRIBUTES_H */

/* Whether sys/capability.h is present */
/* #undef HAVE_SYS_CAPABILITY_H */

/* Define to 1 if you have the <sys/cdefs.h> header file. */
#define HAVE_SYS_CDEFS_H 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/dmapi.h> header file. */
/* #undef HAVE_SYS_DMAPI_H */

/* Define to 1 if you have the <sys/dmi.h> header file. */
/* #undef HAVE_SYS_DMI_H */

/* Define to 1 if you have the <sys/dustat.h> header file. */
/* #undef HAVE_SYS_DUSTAT_H */

/* Define to 1 if you have the <sys/ea.h> header file. */
/* #undef HAVE_SYS_EA_H */

/* Define to 1 if you have the <sys/epoll.h> header file. */
/* #undef HAVE_SYS_EPOLL_H */

/* Define to 1 if you have the <sys/extattr.h> header file. */
/* #undef HAVE_SYS_EXTATTR_H */

/* Define to 1 if you have the <sys/fcntl.h> header file. */
/* #undef HAVE_SYS_FCNTL_H */

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/filio.h> header file. */
/* #undef HAVE_SYS_FILIO_H */

/* Define to 1 if you have the <sys/filsys.h> header file. */
/* #undef HAVE_SYS_FILSYS_H */

/* Define to 1 if you have the <sys/fs/s5param.h> header file. */
/* #undef HAVE_SYS_FS_S5PARAM_H */

/* Define to 1 if you have the <sys/fs/vx_quota.h> header file. */
/* #undef HAVE_SYS_FS_VX_QUOTA_H */

/* Define to 1 if you have the <sys/id.h> header file. */
/* #undef HAVE_SYS_ID_H */

/* Define to 1 if you have the <sys/inotify.h> header file. */
#define HAVE_SYS_INOTIFY_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/ipc.h> header file. */
#define HAVE_SYS_IPC_H 1

/* Define to 1 if you have the <sys/jfsdmapi.h> header file. */
/* #undef HAVE_SYS_JFSDMAPI_H */

/* Whether Linux kernel uses core_pattern for core files */
/* #undef HAVE_SYS_KERNEL_PROC_CORE_PATTERN */

/* Define to 1 if you have the <sys/mman.h> header file. */
#define HAVE_SYS_MMAN_H 1

/* Define to 1 if you have the <sys/mode.h> header file. */
/* #undef HAVE_SYS_MODE_H */

/* Define to 1 if you have the <sys/mount.h> header file. */
#define HAVE_SYS_MOUNT_H 1

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/prctl.h> header file. */
/* #undef HAVE_SYS_PRCTL_H */

/* Define to 1 if you have the <sys/priv.h> header file. */
/* #undef HAVE_SYS_PRIV_H */

/* Define to 1 if you have the <sys/proplist.h> header file. */
/* #undef HAVE_SYS_PROPLIST_H */

/* Define to 1 if you have the <sys/ptrace.h> header file. */
/* #undef HAVE_SYS_PTRACE_H */

/* Whether the new lib/sysquotas.c interface can be used */
/* #undef HAVE_SYS_QUOTAS */

/* Define to 1 if you have the <sys/quota.h> header file. */
/* #undef HAVE_SYS_QUOTA_H */

/* Define to 1 if you have the <sys/resource.h> header file. */
#define HAVE_SYS_RESOURCE_H 1

/* Define to 1 if you have the <sys/security.h> header file. */
/* #undef HAVE_SYS_SECURITY_H */

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/shm.h> header file. */
/* #undef HAVE_SYS_SHM_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/sockio.h> header file. */
#define HAVE_SYS_SOCKIO_H 1

/* Define to 1 if you have the <sys/statfs.h> header file. */
/* #undef HAVE_SYS_STATFS_H */

/* Define to 1 if you have the <sys/statvfs.h> header file. */
#define HAVE_SYS_STATVFS_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/syscall.h> header file. */
/* #undef HAVE_SYS_SYSCALL_H */

/* Define to 1 if you have the <sys/sysctl.h> header file. */
#define HAVE_SYS_SYSCTL_H 1

/* Define to 1 if you have the <sys/syslog.h> header file. */
/* #undef HAVE_SYS_SYSLOG_H */

/* Define to 1 if you have the <sys/sysmacros.h> header file. */
#define HAVE_SYS_SYSMACROS_H 1

/* Define to 1 if you have the <sys/termio.h> header file. */
#define HAVE_SYS_TERMIO_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/ucontext.h> header file. */
/* #undef HAVE_SYS_UCONTEXT_H */

/* Define to 1 if you have the <sys/uio.h> header file. */
#define HAVE_SYS_UIO_H 1

/* Define to 1 if you have the <sys/unistd.h> header file. */
/* #undef HAVE_SYS_UNISTD_H */

/* Define to 1 if you have the <sys/un.h> header file. */
#define HAVE_SYS_UN_H 1

/* Define to 1 if you have the <sys/vfs.h> header file. */
/* #undef HAVE_SYS_VFS_H */

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <sys/xattr.h> header file. */
/* #undef HAVE_SYS_XATTR_H */

/* Whether we have TDB_ERR_NESTING */
#define HAVE_TDB_ERR_NESTING 1

/* Define to 1 if you have the `telldir64' function. */
/* #undef HAVE_TELLDIR64 */

/* Define to 1 if you have the <termios.h> header file. */
#define HAVE_TERMIOS_H 1

/* Define to 1 if you have the <termio.h> header file. */
/* #undef HAVE_TERMIO_H */

/* Define to 1 if you have the `textdomain' function. */
/* #undef HAVE_TEXTDOMAIN */

/* Whether the krb5_ap_req struct has a ticket pointer */
/* #undef HAVE_TICKET_POINTER_IN_KRB5_AP_REQ */

/* Define to 1 if you have the `timegm' function. */
#define HAVE_TIMEGM 1

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Whether Tru64 ACLs are available */
/* #undef HAVE_TRU64_ACLS */

/* Whether crypt needs truncated salt */
/* #undef HAVE_TRUNCATED_SALT */

/* Whether we have ucontext_t */
/* #undef HAVE_UCONTEXT_T */

/* Whether uint16 typedef is included by rpc/rpc.h */
/* #undef HAVE_UINT16_FROM_RPC_RPC_H */

/* Whether uint32 typedef is included by rpc/rpc.h */
/* #undef HAVE_UINT32_FROM_RPC_RPC_H */

/* Define to 1 if the system has the type `uintptr_t'. */
#define HAVE_UINTPTR_T 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* If we need to build with unixscoket support */
#define HAVE_UNIXSOCKET 1

/* Whether UnixWare ACLs are available */
/* #undef HAVE_UNIXWARE_ACLS */

/* Define to 1 if you have the <unix.h> header file. */
#define HAVE_UNIX_H 1

/* Define to 1 if you have the `unsetenv' function. */
#define HAVE_UNSETENV 1

/* Whether the 'unsigned char' type is available */
/* #undef HAVE_UNSIGNED_CHAR */

/* Define to 1 if you have the `updwtmp' function. */
/* #undef HAVE_UPDWTMP */

/* Define to 1 if you have the `updwtmpx' function. */
/* #undef HAVE_UPDWTMPX */

/* Define to 1 if you have the `usleep' function. */
#define HAVE_USLEEP 1

/* Whether struct utimbuf is available */
#define HAVE_UTIMBUF 1

/* Define to 1 if you have the `utime' function. */
#define HAVE_UTIME 1

/* Define to 1 if you have the `utimensat' function. */
#define HAVE_UTIMENSAT 1

/* Define to 1 if you have the `utimes' function. */
#define HAVE_UTIMES 1

/* Define to 1 if you have the <utime.h> header file. */
#define HAVE_UTIME_H 1

/* Define to 1 if you have the <utmpx.h> header file. */
/* #undef HAVE_UTMPX_H */

/* Define to 1 if you have the <utmp.h> header file. */
#define HAVE_UTMP_H 1

/* Whether the utmp struct has a property ut_addr */
/* #undef HAVE_UT_UT_ADDR */

/* Whether the utmp struct has a property ut_addr_v6 */
/* #undef HAVE_UT_UT_ADDR_V6 */

/* Whether the utmp struct has a property ut_exit */
#define HAVE_UT_UT_EXIT 1

/* Whether the utmp struct has a property ut_host */
/* #undef HAVE_UT_UT_HOST */

/* Whether the utmp struct has a property ut_id */
#define HAVE_UT_UT_ID 1

/* Whether the utmp struct has a property ut_name */
#define HAVE_UT_UT_NAME 1

/* Whether the utmp struct has a property ut_pid */
#define HAVE_UT_UT_PID 1

/* Whether the utmp struct has a property ut_time */
#define HAVE_UT_UT_TIME 1

/* Whether the utmp struct has a property ut_tv */
/* #undef HAVE_UT_UT_TV */

/* Whether the utmp struct has a property ut_type */
#define HAVE_UT_UT_TYPE 1

/* Whether the utmp struct has a property ut_user */
#define HAVE_UT_UT_USER 1

/* Define to 1 if you have the `uuid_generate' function. */
/* #undef HAVE_UUID_GENERATE */

/* Define to 1 if you have the <uuid/uuid.h> header file. */
/* #undef HAVE_UUID_UUID_H */

/* Whether the utmpx struct has a property ut_syslen */
/* #undef HAVE_UX_UT_SYSLEN */

/* Define to 1 if you have the <valgrind.h> header file. */
/* #undef HAVE_VALGRIND_H */

/* Define to 1 if you have the <valgrind/memcheck.h> header file. */
/* #undef HAVE_VALGRIND_MEMCHECK_H */

/* Define to 1 if you have the <valgrind/valgrind.h> header file. */
/* #undef HAVE_VALGRIND_VALGRIND_H */

/* Define to 1 if you have the <vararg.h> header file. */
/* #undef HAVE_VARARG_H */

/* Define to 1 if you have the `vasprintf' function. */
/* #undef HAVE_VASPRINTF */

/* Whether va_copy() is available */
#define HAVE_VA_COPY 1

/* Define to 1 if you have the `vdprintf' function. */
/* #undef HAVE_VDPRINTF */

/* Whether the C compiler understands volatile */
#define HAVE_VOLATILE 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the `vsyslog' function. */
#define HAVE_VSYSLOG 1

/* Define to 1 if you have the `wait4' function. */
#define HAVE_WAIT4 1

/* Define to 1 if you have the `waitpid' function. */
#define HAVE_WAITPID 1

/* Define to 1 if you have the <windows.h> header file. */
/* #undef HAVE_WINDOWS_H */

/* Define to 1 if you have the <winsock2.h> header file. */
/* #undef HAVE_WINSOCK2_H */

/* Whether the WRFILE:-keytab is supported */
/* #undef HAVE_WRFILE_KEYTAB */

/* Define to 1 if you have the <ws2tcpip.h> header file. */
/* #undef HAVE_WS2TCPIP_H */

/* Define to 1 if you have the <xfs/dmapi.h> header file. */
/* #undef HAVE_XFS_DMAPI_H */

/* Define to 1 if you have the <xfs/libxfs.h> header file. */
/* #undef HAVE_XFS_LIBXFS_H */

/* Whether xfs quota support is available */
/* #undef HAVE_XFS_QUOTAS */

/* Define to 1 if you have the `yp_get_default_domain' function. */
/* #undef HAVE_YP_GET_DEFAULT_DOMAIN */

/* Define to 1 if you have the `zlibVersion' function. */
#define HAVE_ZLIBVERSION 1

/* Define to 1 if you have the <zlib.h> header file. */
#define HAVE_ZLIB_H 1

/* Define to 1 if you have the `_acl' function. */
/* #undef HAVE__ACL */

/* Whether the _Bool type is available */
#define HAVE__Bool 1

/* Define to 1 if you have the `_chdir' function. */
/* #undef HAVE__CHDIR */

/* Define to 1 if you have the `_close' function. */
/* #undef HAVE__CLOSE */

/* Define to 1 if you have the `_closedir' function. */
/* #undef HAVE__CLOSEDIR */

/* Define to 1 if you have the `_dup' function. */
/* #undef HAVE__DUP */

/* Define to 1 if you have the `_dup2' function. */
/* #undef HAVE__DUP2 */

/* Define to 1 if you have the `_et_list' function. */
/* #undef HAVE__ET_LIST */

/* Define to 1 if you have the `_facl' function. */
/* #undef HAVE__FACL */

/* Define to 1 if you have the `_fchdir' function. */
/* #undef HAVE__FCHDIR */

/* Define to 1 if you have the `_fcntl' function. */
/* #undef HAVE__FCNTL */

/* Define to 1 if you have the `_fork' function. */
#define HAVE__FORK 1

/* Define to 1 if you have the `_fstat' function. */
/* #undef HAVE__FSTAT */

/* Define to 1 if you have the `_fstat64' function. */
/* #undef HAVE__FSTAT64 */

/* Define to 1 if you have the `_getcwd' function. */
/* #undef HAVE__GETCWD */

/* Define to 1 if you have the `_llseek' function. */
/* #undef HAVE__LLSEEK */

/* Define to 1 if you have the `_lseek' function. */
/* #undef HAVE__LSEEK */

/* Define to 1 if you have the `_lstat' function. */
/* #undef HAVE__LSTAT */

/* Define to 1 if you have the `_lstat64' function. */
/* #undef HAVE__LSTAT64 */

/* Define to 1 if you have the `_open' function. */
/* #undef HAVE__OPEN */

/* Define to 1 if you have the `_open64' function. */
/* #undef HAVE__OPEN64 */

/* Define to 1 if you have the `_opendir' function. */
/* #undef HAVE__OPENDIR */

/* Define to 1 if you have the `_pread' function. */
/* #undef HAVE__PREAD */

/* Define to 1 if you have the `_pread64' function. */
/* #undef HAVE__PREAD64 */

/* Define to 1 if you have the `_pwrite' function. */
/* #undef HAVE__PWRITE */

/* Define to 1 if you have the `_pwrite64' function. */
/* #undef HAVE__PWRITE64 */

/* Define to 1 if you have the `_read' function. */
/* #undef HAVE__READ */

/* Define to 1 if you have the `_readdir' function. */
/* #undef HAVE__READDIR */

/* Define to 1 if you have the `_readdir64' function. */
/* #undef HAVE__READDIR64 */

/* Define to 1 if you have the `_seekdir' function. */
/* #undef HAVE__SEEKDIR */

/* Define to 1 if you have the `_stat' function. */
/* #undef HAVE__STAT */

/* Define to 1 if you have the `_stat64' function. */
/* #undef HAVE__STAT64 */

/* Define to 1 if you have the `_telldir' function. */
/* #undef HAVE__TELLDIR */

/* Whether the __VA_ARGS__ macro is available */
#define HAVE__VA_ARGS__MACRO 1

/* Define to 1 if you have the `_write' function. */
/* #undef HAVE__WRITE */

/* Define to 1 if you have the `__acl' function. */
/* #undef HAVE___ACL */

/* Define to 1 if you have the `__chdir' function. */
/* #undef HAVE___CHDIR */

/* Define to 1 if you have the `__close' function. */
/* #undef HAVE___CLOSE */

/* Define to 1 if you have the `__closedir' function. */
/* #undef HAVE___CLOSEDIR */

/* Define to 1 if you have the `__dup' function. */
/* #undef HAVE___DUP */

/* Define to 1 if you have the `__dup2' function. */
/* #undef HAVE___DUP2 */

/* Define to 1 if you have the `__facl' function. */
/* #undef HAVE___FACL */

/* Define to 1 if you have the `__fchdir' function. */
/* #undef HAVE___FCHDIR */

/* Define to 1 if you have the `__fcntl' function. */
/* #undef HAVE___FCNTL */

/* Define to 1 if you have the `__fork' function. */
/* #undef HAVE___FORK */

/* Define to 1 if you have the `__fstat' function. */
/* #undef HAVE___FSTAT */

/* Define to 1 if you have the `__fstat64' function. */
/* #undef HAVE___FSTAT64 */

/* Define to 1 if you have the `__fxstat' function. */
/* #undef HAVE___FXSTAT */

/* Define to 1 if you have the `__getcwd' function. */
/* #undef HAVE___GETCWD */

/* Define to 1 if you have the `__getdents' function. */
/* #undef HAVE___GETDENTS */

/* Define to 1 if you have the `__llseek' function. */
/* #undef HAVE___LLSEEK */

/* Define to 1 if you have the `__lseek' function. */
/* #undef HAVE___LSEEK */

/* Define to 1 if you have the `__lstat' function. */
/* #undef HAVE___LSTAT */

/* Define to 1 if you have the `__lstat64' function. */
/* #undef HAVE___LSTAT64 */

/* Define to 1 if you have the `__lxstat' function. */
/* #undef HAVE___LXSTAT */

/* Whether __NR_inotify_init() is available */
/* #undef HAVE___NR_INOTIFY_INIT_DECL */

/* Define to 1 if you have the `__open' function. */
/* #undef HAVE___OPEN */

/* Define to 1 if you have the `__open64' function. */
/* #undef HAVE___OPEN64 */

/* Define to 1 if you have the `__opendir' function. */
/* #undef HAVE___OPENDIR */

/* Define to 1 if you have the `__pread' function. */
/* #undef HAVE___PREAD */

/* Define to 1 if you have the `__pread64' function. */
/* #undef HAVE___PREAD64 */

/* Define to 1 if you have the `__pwrite' function. */
/* #undef HAVE___PWRITE */

/* Define to 1 if you have the `__pwrite64' function. */
/* #undef HAVE___PWRITE64 */

/* Define to 1 if you have the `__read' function. */
/* #undef HAVE___READ */

/* Define to 1 if you have the `__readdir' function. */
/* #undef HAVE___READDIR */

/* Define to 1 if you have the `__readdir64' function. */
/* #undef HAVE___READDIR64 */

/* Define to 1 if you have the `__seekdir' function. */
/* #undef HAVE___SEEKDIR */

/* Defined if struct sockaddr_storage has __ss_family field */
/* #undef HAVE___SS_FAMILY */

/* Define to 1 if you have the `__stat' function. */
/* #undef HAVE___STAT */

/* Define to 1 if you have the `__stat64' function. */
/* #undef HAVE___STAT64 */

/* Define to 1 if you have the `__strtoll' function. */
/* #undef HAVE___STRTOLL */

/* Define to 1 if you have the `__strtoull' function. */
/* #undef HAVE___STRTOULL */

/* Define to 1 if you have the `__sys_llseek' function. */
/* #undef HAVE___SYS_LLSEEK */

/* Define to 1 if you have the `__telldir' function. */
/* #undef HAVE___TELLDIR */

/* Whether __va_copy() is available */
/* #undef HAVE___VA_COPY */

/* Define to 1 if you have the `__write' function. */
/* #undef HAVE___WRITE */

/* Define to 1 if you have the `__xstat' function. */
/* #undef HAVE___XSTAT */

/* Whether there is a __func__ macro */
/* #undef HAVE_func_MACRO */

/* Whether the host os is HPUX */
/* #undef HPUX */

/* Whether the hpux sendfile() API is available */
/* #undef HPUX_SENDFILE_API */

/* Whether the host os is irix */
/* #undef IRIX */

/* Whether the host os is irix6 */
/* #undef IRIX6 */

/* Whether krb5_get_init_creds_opt_free takes a context argument */
/* #undef KRB5_CREDS_OPT_FREE_REQUIRES_CONTEXT */

/* Whether krb5_princ_realm returns krb5_realm or krb5_data */
/* #undef KRB5_PRINC_REALM_RETURNS_REALM */

/* Whether the krb5_ticket structure contains the kvno and enctype */
/* #undef KRB5_TICKET_HAS_KEYINFO */

/* Number of arguments to krb5_verify_checksum */
/* #undef KRB5_VERIFY_CHECKSUM_ARGS */

/* Number of arguments to ldap_set_rebind_proc */
/* #undef LDAP_SET_REBIND_PROC_ARGS */

/* LIBREPLACE_NETWORK_CHECKS were used */
#define LIBREPLACE_NETWORK_CHECKS 1

/* Whether the host os is linux */
/* #undef LINUX */

/* Whether (linux) sendfile() is broken */
/* #undef LINUX_BROKEN_SENDFILE_API */

/* Whether linux sendfile() API is available */
/* #undef LINUX_SENDFILE_API */

/* Whether MMAP is broken */
/* #undef MMAP_BLACKLIST */

/* Whether the host os is NeXT v2 */
/* #undef NEXT2 */

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Use nss wrapper library */
/* #undef NSS_WRAPPER */

/* Whether the host os is osf1 */
/* #undef OSF1 */

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "samba-technical@samba.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Samba"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Samba 3"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "samba"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "3"

/* Does a POSIX ACL need a mask element */
/* #undef POSIX_ACL_NEEDS_MASK */

/* Whether pututline returns pointer */
/* #undef PUTUTLINE_RETURNS_UTMP */

/* Whether the host os is qnx */
#define QNX 1

/* Whether the realpath function allows NULL */
/* #undef REALPATH_TAKES_NULL */

/* Whether the host os is reliantunix */
/* #undef RELIANTUNIX */

/* Whether getpass should be replaced */
#define REPLACE_GETPASS 1

/* getpass returns <9 chars where getpassphrase returns <265 chars */
/* #undef REPLACE_GETPASS_BY_GETPASSPHRASE */

/* Whether inet_ntoa should be replaced */
/* #undef REPLACE_INET_NTOA */

/* replace readdir */
/* #undef REPLACE_READDIR */

/* replace readdir using getdents() */
/* #undef REPLACE_READDIR_GETDENTS */

/* replace readdir using getdirentries() */
/* #undef REPLACE_READDIR_GETDIRENTRIES */

/* Whether strptime should be replaced */
#define REPLACE_STRPTIME 1

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Whether the host os is sco unix */
/* #undef SCO */

/* Whether seekdir returns an int */
/* #undef SEEKDIR_RETURNS_INT */

/* Whether seekdir returns void */
#define SEEKDIR_RETURNS_VOID 1

/* Shared library extension */
#define SHLIBEXT "so"

/* The size of `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of the 'dev_t' type */
/* #undef SIZEOF_DEV_T */

/* The size of the 'ino_t' type */
/* #undef SIZEOF_INO_T */

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 8

/* The size of `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* The size of the 'off_t' type */
#define SIZEOF_OFF_T 8

/* The size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* The size of `size_t', as computed by sizeof. */
#define SIZEOF_SIZE_T 8

/* The size of `ssize_t', as computed by sizeof. */
#define SIZEOF_SSIZE_T 8

/* The size of the 'time_t' type */
/* #undef SIZEOF_TIME_T */

/* The size of `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 8

/* Use socket wrapper library */
/* #undef SOCKET_WRAPPER */

/* getgrent_r irix (similar to solaris) function prototype */
/* #undef SOLARIS_GETGRENT_R */

/* getpwent_r irix (similar to solaris) function prototype */
/* #undef SOLARIS_GETPWENT_R */

/* Whether the solaris sendfile() API is available */
/* #undef SOLARIS_SENDFILE_API */

/* Whether statfs requires two arguments and struct statfs has bsize property
   */
/* #undef STAT_STATFS2_BSIZE */

/* Whether statfs requires 2 arguments and struct statfs has fsize */
/* #undef STAT_STATFS2_FSIZE */

/* Whether statfs requires 2 arguments and struct fs_data is available */
/* #undef STAT_STATFS2_FS_DATA */

/* Whether statfs requires 3 arguments */
/* #undef STAT_STATFS3_OSF1 */

/* Whether statfs requires 4 arguments */
/* #undef STAT_STATFS4 */

/* Whether statvfs() is available */
#define STAT_STATVFS 1

/* Whether statvfs64() is available */
/* #undef STAT_STATVFS64 */

/* The size of a block */
#define STAT_ST_BLOCKSIZE 512

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* String list of builtin modules */
#define STRING_STATIC_MODULES " pdb_smbpasswd pdb_tdbsam pdb_wbc_sam idmap_tdb idmap_passdb idmap_nss nss_info_template auth_sam auth_unix auth_winbind auth_wbc auth_server auth_domain auth_builtin vfs_default vfs_posixacl"

/* Whether the host os is sunos4 */
/* #undef SUNOS4 */

/* Whether the host os is solaris */
/* #undef SUNOS5 */

/* Whether sysconf(_SC_NGROUPS_MAX) is available */
#define SYSCONF_SC_NGROUPS_MAX 1

/* Whether sysconf(_SC_NPROCESSORS_ONLN) is available */
#define SYSCONF_SC_NPROCESSORS_ONLN 1

/* Whether sysconf(_SC_NPROC_ONLN) is available */
/* #undef SYSCONF_SC_NPROC_ONLN */

/* Whether sysconf(_SC_PAGESIZE) is available */
#define SYSCONF_SC_PAGESIZE 1

/* syslog facility to log to */
/* #undef SYSLOG_FACILITY */

/* Whether this is a system V system */
/* #undef SYSV */

/* Whether telldir takes a const pointer */
/* #undef TELLDIR_TAKES_CONST_DIR */

/* The maximum value of the 'time_t' type */
/* #undef TIME_T_MAX */

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Whether the host os is unixware */
/* #undef UNIXWARE */

/* Whether to use both of HPUX' crypt calls */
/* #undef USE_BOTH_CRYPT_CALLS */

/* Whether we should build DMAPI integration components */
/* #undef USE_DMAPI */

/* Whether seteuid() is available */
/* #undef USE_SETEUID */

/* Whether setresuid() is available */
/* #undef USE_SETRESUID */

/* Whether setreuid() is available */
/* #undef USE_SETREUID */

/* Whether setuidx() is available */
/* #undef USE_SETUIDX */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Whether we have valgrind headers */
/* #undef VALGRIND */

/* Whether to include Active Directory support */
/* #undef WITH_ADS */

/* Whether to include AFS clear-text auth support */
/* #undef WITH_AFS */

/* Using asynchronous io */
/* #undef WITH_AIO */

/* Whether to include automount support */
/* #undef WITH_AUTOMOUNT */

/* Whether to enable avahi support */
/* #undef WITH_AVAHI_SUPPORT */

/* Whether to include DFS support */
/* #undef WITH_DFS */

/* Whether to enable DNS service discovery support */
/* #undef WITH_DNSSD_SUPPORT */

/* Whether to enable DNS Update support */
/* #undef WITH_DNS_UPDATES */

/* Whether to include AFS fake-kaserver support */
/* #undef WITH_FAKE_KASERVER */

/* Whether to include nisplus_home support */
/* #undef WITH_NISPLUS_HOME */

/* Whether to include PAM support */
#define WITH_PAM 1

/* Whether to include PAM MODULES support */
#define WITH_PAM_MODULES 1

/* Whether to use profiling */
/* #undef WITH_PROFILE */

/* Whether to include pthreadpool helpers */
/* #undef WITH_PTHREADPOOL */

/* Whether to use disk quota support */
/* #undef WITH_QUOTAS */

/* Whether to include sendfile() support */
/* #undef WITH_SENDFILE */

/* Whether to include experimental syslog support */
/* #undef WITH_SYSLOG */

/* Whether to include experimental utmp accounting */
#define WITH_UTMP 1

/* Whether to build winbind */
/* #undef WITH_WINBIND */

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* xattr functions have additional options */
/* #undef XATTR_ADD_OPT */

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* File offset bits */
/* #undef _FILE_OFFSET_BITS */

/* Whether to use GNU libc extensions */
#define _GNU_SOURCE 1

/* Whether to enable large file support */
#define _LARGEFILE64_SOURCE 1

/* Whether to enable large file support */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */


#ifndef _OSF_SOURCE
/* # undef _OSF_SOURCE */
#endif


/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Whether to enable POSIX support */
/* #undef _POSIX_C_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Whether to enable System V compatibility */
/* #undef _SYSV */


#ifndef _XOPEN_SOURCE
/* # undef _XOPEN_SOURCE */
#endif



#ifndef _XOPEN_SOURCE_EXTENDED
# define _XOPEN_SOURCE_EXTENDED 1
#endif


/* Define to 1 if type `char' is unsigned and you are not using gcc.  */
#ifndef __CHAR_UNSIGNED__
/* # undef __CHAR_UNSIGNED__ */
#endif

/* Whether to build auth_builtin as shared module */
/* #undef auth_builtin_init */

/* Whether to build auth_domain as shared module */
/* #undef auth_domain_init */

/* Whether to build auth_netlogond as shared module */
/* #undef auth_netlogond_init */

/* Whether to build auth_sam as shared module */
/* #undef auth_sam_init */

/* Whether to build auth_script as shared module */
#define auth_script_init init_samba_module

/* Whether to build auth_server as shared module */
/* #undef auth_server_init */

/* Whether to build auth_unix as shared module */
/* #undef auth_unix_init */

/* Whether to build auth_wbc as shared module */
/* #undef auth_wbc_init */

/* Whether to build auth_winbind as shared module */
/* #undef auth_winbind_init */

/* Whether to build charset_CP437 as shared module */
#define charset_CP437_init init_samba_module

/* Whether to build charset_CP850 as shared module */
#define charset_CP850_init init_samba_module

/* Whether to build charset_macosxfs as shared module */
/* #undef charset_macosxfs_init */

/* Whether to build charset_weird as shared module */
/* #undef charset_weird_init */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* ctdb ipv4 support */
/* #undef ctdb_control_tcp */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Whether to build gpext_registry as shared module */
/* #undef gpext_registry_init */

/* Whether to build gpext_scripts as shared module */
/* #undef gpext_scripts_init */

/* Whether to build gpext_security as shared module */
/* #undef gpext_security_init */

/* Whether to build idmap_ad as shared module */
/* #undef idmap_ad_init */

/* Whether to build idmap_adex as shared module */
/* #undef idmap_adex_init */

/* Whether to build idmap_autorid as shared module */
#define idmap_autorid_init init_samba_module

/* Whether to build idmap_hash as shared module */
/* #undef idmap_hash_init */

/* Whether to build idmap_ldap as shared module */
/* #undef idmap_ldap_init */

/* Whether to build idmap_nss as shared module */
/* #undef idmap_nss_init */

/* Whether to build idmap_passdb as shared module */
/* #undef idmap_passdb_init */

/* Whether to build idmap_rid as shared module */
/* #undef idmap_rid_init */

/* Whether to build idmap_tdb2 as shared module */
/* #undef idmap_tdb2_init */

/* Whether to build idmap_tdb as shared module */
/* #undef idmap_tdb_init */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `unsigned' if <sys/types.h> does not define. */
/* #undef ino_t */

/* Define to `short' if <sys/types.h> does not define. */
/* #undef int16_t */

/* Define to `long' if <sys/types.h> does not define. */
/* #undef int32_t */

/* Define to `long long' if <sys/types.h> does not define. */
/* #undef int64_t */

/* Define to `char' if <sys/types.h> does not define. */
/* #undef int8_t */

/* Define to `unsigned long' if <sys/types.h> does not define. */
/* #undef intptr_t */

/* Define to `off_t' if <sys/types.h> does not define. */
#define loff_t off_t

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Whether to build nss_info_template as shared module */
/* #undef nss_info_template_init */

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `loff_t' if <sys/types.h> does not define. */
#define offset_t loff_t

/* Whether to build pdb_ads as shared module */
/* #undef pdb_ads_init */

/* Whether to build pdb_ldap as shared module */
/* #undef pdb_ldap_init */

/* Whether to build pdb_smbpasswd as shared module */
/* #undef pdb_smbpasswd_init */

/* Whether to build pdb_tdbsam as shared module */
/* #undef pdb_tdbsam_init */

/* Whether to build pdb_wbc_sam as shared module */
/* #undef pdb_wbc_sam_init */

/* Whether to build perfcount_onefs as shared module */
/* #undef perfcount_onefs_init */

/* Whether to build perfcount_test as shared module */
/* #undef perfcount_test_init */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef ssize_t */

/* Decl of Static init functions */
#define static_decl_auth extern NTSTATUS auth_sam_init(void); extern NTSTATUS auth_unix_init(void); extern NTSTATUS auth_winbind_init(void); extern NTSTATUS auth_wbc_init(void); extern NTSTATUS auth_server_init(void); extern NTSTATUS auth_domain_init(void); extern NTSTATUS auth_builtin_init(void);

/* Decl of Static init functions */
#define static_decl_charset 

/* Decl of Static init functions */
#define static_decl_gpext 

/* Decl of Static init functions */
#define static_decl_idmap extern NTSTATUS idmap_tdb_init(void); extern NTSTATUS idmap_passdb_init(void); extern NTSTATUS idmap_nss_init(void);

/* Decl of Static init functions */
#define static_decl_nss_info extern NTSTATUS nss_info_template_init(void);

/* Decl of Static init functions */
#define static_decl_pdb extern NTSTATUS pdb_smbpasswd_init(void); extern NTSTATUS pdb_tdbsam_init(void); extern NTSTATUS pdb_wbc_sam_init(void);

/* Decl of Static init functions */
#define static_decl_perfcount 

/* Decl of Static init functions */
#define static_decl_vfs extern NTSTATUS vfs_default_init(void); extern NTSTATUS vfs_posixacl_init(void);

/* Static init functions */
#define static_init_auth {  auth_sam_init();  auth_unix_init();  auth_winbind_init();  auth_wbc_init();  auth_server_init();  auth_domain_init();  auth_builtin_init();}

/* Static init functions */
#define static_init_charset {}

/* Static init functions */
#define static_init_gpext {}

/* Static init functions */
#define static_init_idmap {  idmap_tdb_init();  idmap_passdb_init();  idmap_nss_init();}

/* Static init functions */
#define static_init_nss_info {  nss_info_template_init();}

/* Static init functions */
#define static_init_pdb {  pdb_smbpasswd_init();  pdb_tdbsam_init();  pdb_wbc_sam_init();}

/* Static init functions */
#define static_init_perfcount {}

/* Static init functions */
#define static_init_vfs {  vfs_default_init();  vfs_posixacl_init();}

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define to `unsigned short' if <sys/types.h> does not define. */
/* #undef uint16_t */

/* Define to `unsigned long' if <sys/types.h> does not define. */
/* #undef uint32_t */

/* Define to `unsigned long long' if <sys/types.h> does not define. */
/* #undef uint64_t */

/* Define to `unsigned char' if <sys/types.h> does not define. */
/* #undef uint8_t */

/* Whether to build vfs_acl_tdb as shared module */
#define vfs_acl_tdb_init init_samba_module

/* Whether to build vfs_acl_xattr as shared module */
#define vfs_acl_xattr_init init_samba_module

/* Whether to build vfs_afsacl as shared module */
/* #undef vfs_afsacl_init */

/* Whether to build vfs_aio_fork as shared module */
/* #undef vfs_aio_fork_init */

/* Whether to build vfs_aio_pthread as shared module */
/* #undef vfs_aio_pthread_init */

/* Whether to build vfs_aixacl2 as shared module */
/* #undef vfs_aixacl2_init */

/* Whether to build vfs_aixacl as shared module */
/* #undef vfs_aixacl_init */

/* Whether to build vfs_audit as shared module */
#define vfs_audit_init init_samba_module

/* Whether to build vfs_cacheprime as shared module */
/* #undef vfs_cacheprime_init */

/* Whether to build vfs_cap as shared module */
#define vfs_cap_init init_samba_module

/* Whether to build vfs_catia as shared module */
#define vfs_catia_init init_samba_module

/* Whether to build vfs_commit as shared module */
/* #undef vfs_commit_init */

/* Whether to build vfs_crossrename as shared module */
#define vfs_crossrename_init init_samba_module

/* Whether to build vfs_default as shared module */
/* #undef vfs_default_init */

/* Whether to build vfs_default_quota as shared module */
#define vfs_default_quota_init init_samba_module

/* Whether to build vfs_dirsort as shared module */
#define vfs_dirsort_init init_samba_module

/* Whether to build vfs_expand_msdfs as shared module */
#define vfs_expand_msdfs_init init_samba_module

/* Whether to build vfs_extd_audit as shared module */
#define vfs_extd_audit_init init_samba_module

/* Whether to build vfs_fake_perms as shared module */
#define vfs_fake_perms_init init_samba_module

/* Whether to build vfs_fileid as shared module */
/* #undef vfs_fileid_init */

/* Whether to build vfs_full_audit as shared module */
#define vfs_full_audit_init init_samba_module

/* Whether to build vfs_gpfs_hsm_notify as shared module */
/* #undef vfs_gpfs_hsm_notify_init */

/* Whether to build vfs_gpfs as shared module */
/* #undef vfs_gpfs_init */

/* Whether to build vfs_hpuxacl as shared module */
/* #undef vfs_hpuxacl_init */

/* Whether to build vfs_irixacl as shared module */
/* #undef vfs_irixacl_init */

/* Whether to build vfs_linux_xfs_sgid as shared module */
#define vfs_linux_xfs_sgid_init init_samba_module

/* Whether to build vfs_netatalk as shared module */
#define vfs_netatalk_init init_samba_module

/* Whether to build vfs_notify_fam as shared module */
/* #undef vfs_notify_fam_init */

/* Whether to build vfs_onefs as shared module */
/* #undef vfs_onefs_init */

/* Whether to build vfs_onefs_shadow_copy as shared module */
/* #undef vfs_onefs_shadow_copy_init */

/* Whether to build vfs_posixacl as shared module */
/* #undef vfs_posixacl_init */

/* Whether to build vfs_prealloc as shared module */
/* #undef vfs_prealloc_init */

/* Whether to build vfs_preopen as shared module */
#define vfs_preopen_init init_samba_module

/* Whether to build vfs_readahead as shared module */
#define vfs_readahead_init init_samba_module

/* Whether to build vfs_readonly as shared module */
#define vfs_readonly_init init_samba_module

/* Whether to build vfs_recycle as shared module */
#define vfs_recycle_init init_samba_module

/* Whether to build vfs_scannedonly as shared module */
#define vfs_scannedonly_init init_samba_module

/* Whether to build vfs_shadow_copy2 as shared module */
#define vfs_shadow_copy2_init init_samba_module

/* Whether to build vfs_shadow_copy as shared module */
#define vfs_shadow_copy_init init_samba_module

/* Whether to build vfs_smb_traffic_analyzer as shared module */
#define vfs_smb_traffic_analyzer_init init_samba_module

/* Whether to build vfs_solarisacl as shared module */
/* #undef vfs_solarisacl_init */

/* Whether to build vfs_streams_depot as shared module */
#define vfs_streams_depot_init init_samba_module

/* Whether to build vfs_streams_xattr as shared module */
#define vfs_streams_xattr_init init_samba_module

/* Whether to build vfs_syncops as shared module */
#define vfs_syncops_init init_samba_module

/* Whether to build vfs_time_audit as shared module */
#define vfs_time_audit_init init_samba_module

/* Whether to build vfs_tru64acl as shared module */
/* #undef vfs_tru64acl_init */

/* Whether to build vfs_tsmsm as shared module */
/* #undef vfs_tsmsm_init */

/* Whether to build vfs_xattr_tdb as shared module */
#define vfs_xattr_tdb_init init_samba_module

/* Whether to build vfs_zfsacl as shared module */
/* #undef vfs_zfsacl_init */

/* Define to `unsigned short' if <sys/types.h> does not define. */
/* #undef wchar_t */
