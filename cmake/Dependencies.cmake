include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 12.2.0
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(fmt)
