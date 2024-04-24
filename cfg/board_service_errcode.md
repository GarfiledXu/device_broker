# [某个时刻的错误码值=n个状态成员(相或)相加值，eg:201=1+8+40+64+128=RETURN_SUCCESS+UPLOADED+UPLOAD_SUCCESS+DIVORCED]
# [task] [status member]
STATE_DEVICE_INVALID = -1

FREE = 1

BUSY = 2

UPDATINTG = 4

UPDATED = 8

UPDATE_SUCCESS = 16

UPDATE_FAIL = 32

<!-- REBOOTING = 64 -->
REBOOTING = 64
<!-- REBOOT_SUCCESS = 128 -->
REBOOT_SUCCESS = 128
# [device] [status member]
STATE_TASK_INVALID = -1

DIVORCED = 1

ACCEPTED = 2

RUNNING = 4

RETURN_SUCCESS = 8

RETURN_ERROR = 16

UPLOADING = 32

UPLOADED = 64

UPLOAD_SUCCESS = 128

UPLOAD_FAIL = 256

CALL_FAILED = 512
# [task] [status error code value <==> msg table]
**1 = [DIVORCED] 无任务状态**

**514 = [ACCEPTED CALL_FAILED  ] testbed启动失败**

**6 = [ACCEPTED RUNNING] 接收任务，运行中**

**8 = [RETURN_SUCCESS] testbed结束，返回成功**

**513 = [CALL_FAILED DIVORCED ] testbed启动失败, 无任务状态**

**17 = [RETURN_ERROR DIVORCED] testbed结束，返回失败，无任务状态**

**201 = [RETURN_SUCCESS UPLOADED UPLOAD_SUCCESS DIVORCED] testbed结束，返回成功，上传结束，上传成功，无任务状态**

**329 = [RETURN_SUCCESS UPLOADED UPLOAD_FAIL DIVORCED] testbed结束，返回成功，上传结束，上传失败，无任务状态**



# [device] [status error code value <==> msg table]
**1 = [FREE] 空闲**

**2 = [BUSY] 繁忙**

**6 = [UPDATINTG BUSY] 繁忙，更新中**

**25 = [UPDATED UPDATE_SUCCESS  FREE] 更新结束， 更新成功，空闲**

**41 = [UPDATED UPDATE_FAIL FREE] 更新结束， 更新失败，空闲**

<!-- **129 = [BUSY  REBOOTING] 繁忙，重启中** -->
<!-- **66 = [BUSY  REBOOTING] 繁忙，重启中** -->
<!-- **130 = [BUSY  REBOOTING] 繁忙，重启中** -->
**66 = [BUSY  REBOOTING] 繁忙，重启中**
## [date:2023/02/07]
## [date:2023/02/15]