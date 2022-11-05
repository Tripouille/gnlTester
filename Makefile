TIMEOUT_US				= 1000000

.DEFAULT_GOAL			= a
UTILS					= utils/sigsegv.cpp utils/color.cpp utils/check.cpp utils/gnl.cpp utils/leaks.cpp
TESTS_PATH				= tests/
SHELL					= bash


MANDATORY_HEADER		= ../get_next_line.h
MANDATORY_FILES			= ../get_next_line.c ../get_next_line_utils.c
MANDATORY_OBJS			= $(MANDATORY_FILES:../%.c=%.o)

BONUS_HEADER			= ../get_next_line_bonus.h
BONUS_FILES				= ../get_next_line_bonus.c ../get_next_line_utils_bonus.c
BONUS_OBJS				= $(BONUS_FILES:../%.c=%.o)

MANDATORY				= mandatory
1MANDATORY				= $(addprefix 1, $(MANDATORY))
42MANDATORY				= $(addprefix 42, $(MANDATORY))
10MMANDATORY			= $(addprefix 10M, $(MANDATORY))


BONUS					= bonus
1MBONUS					= $(addprefix m1, $(BONUS))
42MBONUS				= $(addprefix m42, $(BONUS))
10MMBONUS				= $(addprefix m10M, $(BONUS))

1BONUS					= $(addprefix 1, $(BONUS))
42BONUS					= $(addprefix 42, $(BONUS))
10MBONUS				= $(addprefix 10M, $(BONUS))

CFLAGS					= -g3 -Wall -Wextra -Werror
CPPFLAGS				= -g3 -ldl -std=c++11 -I utils/ -I.. -Wno-everything

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
    VALGRIND = valgrind -q --leak-check=full
endif

$(1MANDATORY): 1%:
	@gcc -D BUFFER_SIZE=1 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=1 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(42MANDATORY): 42%:
	@gcc -D BUFFER_SIZE=42 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=42 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(10MMANDATORY): 10M%:
	@gcc -D BUFFER_SIZE=10000000 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=10000000 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest


$(1BONUS): 1%:
	@gcc -D BUFFER_SIZE=1 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=1 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(BONUS_OBJS) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(42BONUS): 42%:
	@gcc -D BUFFER_SIZE=42 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=42 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(BONUS_OBJS) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(10MBONUS): 10M%:
	@gcc -D BUFFER_SIZE=10000000 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=10000000 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(BONUS_OBJS) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest

$(1MBONUS): m1%:
	@gcc -D BUFFER_SIZE=1 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=1 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$(MANDATORY).cpp $(BONUS_OBJS) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(42MBONUS): m42%:
	@gcc -D BUFFER_SIZE=42 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=42 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$(MANDATORY).cpp $(BONUS_OBJS) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest
$(10MMBONUS): m10M%:
	@gcc -D BUFFER_SIZE=10000000 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=10000000 -gdwarf-4 -D TIMEOUT_US=$(TIMEOUT_US) $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$(MANDATORY).cpp $(BONUS_OBJS) -o gnlTest && $(VALGRIND) ./gnlTest < files/alternate_line_nl_with_nl && rm -f gnlTest

mandatory_start: update
	@tput setaf 4 && echo [Mandatory]

bonus_start: update
	@tput setaf 3 && printf "[Static = " && cat ../*bonus.c | grep -E 'static.*;' | wc -l | tr -d '\n' | xargs /bin/echo -n && printf "]\n"
	@tput setaf 5 && /bin/echo [Bonus]

update:
	@git pull

dockerm dockerb dockera: docker%:
	@docker rm -f mc > /dev/null 2>&1 || true
	docker build -qt mi .
	docker run -dti --name mc -v $(shell dirname $(shell pwd)):/project/ mi
	docker exec -ti mc make $* -C gnlTester || true
	@docker rm -f mc > /dev/null 2>&1

m: mandatory_start $(1MANDATORY) $(42MANDATORY) $(10MMANDATORY) cleanMandatory
b: bonus_start $(1MBONUS) $(42MBONUS) $(10MMBONUS) $(1BONUS) $(42BONUS) $(10MBONUS) cleanBonus
a: m b

fclean clean cleanMandatory cleanBonus:
	@rm -rf $(MANDATORY_OBJS) $(BONUS_OBJS) gnlTest*

.PHONY:	mandatory_start m bonus_start b a fclean clean cleanMandatory cleanBonus
