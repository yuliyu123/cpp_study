set (ut_src
	TimerTest.cc
	# ThreadPool.cc
)

add_library(ut_test STATIC
    ${ut_src}
)
