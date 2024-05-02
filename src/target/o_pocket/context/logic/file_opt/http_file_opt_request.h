#pragma once

#include "http_body_cvt.h"
#include "file_pull.h"
#include "file_clear.h"
#include "filesystem_impl.inl"

#include "state_suit.h"
#include "task_suit.h"
using namespace ns;

TaskSuitBase::TaskReturn file_operation_file_pull(TaskFileOperation_FilePull file_pull_info);
TaskSuitBase::TaskReturn file_operation_file_clear(TaskFileOperation_FileClear file_clear_info);