.DEFAULT_GOAL			= va
UTILS					= utils/sigsegv.cpp utils/color.cpp utils/check.cpp
TESTS_PATH				= tests/
SHELL					= bash

MANDATORY_HEADER		= ../get_next_line.h
MANDATORY_FILES			= ../get_next_line.c ../get_next_line_utils.c
MANDATORY_OBJS			= $(MANDATORY_FILES:../%.c=%.o)

MANDATORY				= mandatory
1MANDATORY				= $(addprefix 1, $(MANDATORY))
42MANDATORY				= $(addprefix 42, $(MANDATORY))
10MMANDATORY			= $(addprefix 10M, $(MANDATORY))

V1MANDATORY				= $(addprefix v1, $(MANDATORY))
V42MANDATORY			= $(addprefix v42, $(MANDATORY))
V10MMANDATORY			= $(addprefix v10M, $(MANDATORY))


BONUS_HEADER			= ../get_next_line_bonus.h
BONUS_FILES				= ../get_next_line_bonus.c ../get_next_line_utils_bonus.c
BONUS_OBJS				= $(BONUS_FILES:../%.c=%.o)

BONUS					= bonus
1BONUS					= $(addprefix 1, $(BONUS))
42BONUS					= $(addprefix 42, $(BONUS))
10MBONUS				= $(addprefix 10M, $(BONUS))

V1BONUS					= $(addprefix v1, $(BONUS))
V42BONUS				= $(addprefix v42, $(BONUS))
V10MBONUS				= $(addprefix v10M, $(BONUS))

CFLAGS					= -Wall -Wextra -Werror
CPPFLAGS				= -g3 -std=c++11 -I utils/ -I..
VALGRIND				= valgrind -q --leak-check=full --show-reachable=yes

$(1MANDATORY): 1%:
	@gcc -D BUFFER_SIZE=1 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=1 $(CPPFLAGS) -fsanitize=address $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && ./a.out && rm -f a.out

$(42MANDATORY): 42%:
	@gcc -D BUFFER_SIZE=42 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=42 $(CPPFLAGS) -fsanitize=address $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && ./a.out && rm -f a.out

$(10MMANDATORY): 10M%:
	@gcc -D BUFFER_SIZE=10000000 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=10000000 $(CPPFLAGS) -fsanitize=address $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && ./a.out && rm -f a.out

$(V1MANDATORY): v1%:
	@gcc -D BUFFER_SIZE=1 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=1 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && $(VALGRIND) ./a.out && rm -f a.out

$(V42MANDATORY): v42%:
	@gcc -D BUFFER_SIZE=42 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=42 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && $(VALGRIND) ./a.out && rm -f a.out

$(V10MMANDATORY): v10M%:
	@gcc -D BUFFER_SIZE=10000000 $(CFLAGS) -c $(MANDATORY_FILES)
	@clang++ -D BUFFER_SIZE=10000000 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(MANDATORY_OBJS) && $(VALGRIND) ./a.out && rm -f a.out


$(1BONUS): 1%:
	@gcc -D BUFFER_SIZE=1 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=1 $(CPPFLAGS) -fsanitize=address $(UTILS) $(TESTS_PATH)$*.cpp $(BONUS_OBJS) && ./a.out && rm -f a.out

$(42BONUS): 42%:
	@gcc -D BUFFER_SIZE=42 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=42 $(CPPFLAGS) -fsanitize=address $(UTILS) $(TESTS_PATH)$*.cpp $(BONUS_OBJS) && ./a.out && rm -f a.out

$(10MBONUS): 10M%:
	@gcc -D BUFFER_SIZE=10000000 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=10000000 $(CPPFLAGS) -fsanitize=address $(UTILS) $(TESTS_PATH)$*.cpp $(BONUS_OBJS) && ./a.out && rm -f a.out

$(V1BONUS): v1%:
	@gcc -D BUFFER_SIZE=1 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=1 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(BONUS_OBJS) && $(VALGRIND) ./a.out && rm -f a.out

$(V42BONUS): v42%:
	@gcc -D BUFFER_SIZE=42 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=42 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(BONUS_OBJS) && $(VALGRIND) ./a.out && rm -f a.out

$(V10MBONUS): v10M%:
	@gcc -D BUFFER_SIZE=10000000 $(CFLAGS) -c $(BONUS_FILES)
	@clang++ -D BUFFER_SIZE=10000000 $(CPPFLAGS) $(UTILS) $(TESTS_PATH)$*.cpp $(BONUS_OBJS) && $(VALGRIND) ./a.out && rm -f a.out

mandatory_start: update
	@tput setaf 4 && echo [Mandatory]

bonus_start: update
	@tput setaf 3 && printf "[Static = " && cat ../*bonus* | grep static | wc -l | tr -d '\n' | xargs /bin/echo -n && printf "]\n"
	@tput setaf 5 && /bin/echo [Bonus]

update:
	@git pull

m: mandatory_start $(1MANDATORY) $(42MANDATORY) $(10MMANDATORY) cleanMandatory
b: bonus_start $(1BONUS) $(42BONUS) $(10MBONUS) cleanBonus
a: m b

vm: mandatory_start $(V1MANDATORY) $(V42MANDATORY) $(V10MMANDATORY) cleanMandatory
vb: bonus_start $(V1BONUS) $(V42BONUS) $(V10MBONUS) cleanBonus
va: vm vb

cleanMandatory cleanBonus:
	@rm -rf $(MANDATORY_OBJS) $(BONUS_OBJS)

.PHONY:	mandatory_start m vm bonus_start b vb a va cleanMandatory cleanBonus