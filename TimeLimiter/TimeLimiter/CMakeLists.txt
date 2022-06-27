cmake_minimum_required (VERSION 3.8)

set(H_TIMELIMITER "TimeLimiter.cpp" "TimeLimiter.h")
set(H_TIMESERVINVOKER "TimeServerInvoker.cpp" "TimeServerInvoker.h")

add_executable (TimeLimiter "main.cpp" ${H_TIMELIMITER} ${H_TIMESERVINVOKER})
