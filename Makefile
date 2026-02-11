################################################################################
#                                   VARIABLES                                  #
################################################################################

NAME		:= computorv2
CXX			:= c++
CXXFLAGS	:= -Werror -Wall -Wextra -std=c++20 -MMD -MP -Iincludes -Iincludes/Types -Iincludes/Nodes -Iincludes/Visitors

SRCS_PATH = ./srcs/
OBJS_PATH = .obj/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))
OBJS = $(SRCS:$(SRCS_PATH)%.cpp=$(OBJS_PATH)%.o)

################################################################################
#                                   SRCS_FILES                                 #
################################################################################

SRCS_FILES =	main.cpp \
				Parser.cpp \
				parse_and_assign.cpp \
				lexer.cpp \
				pre_pass.cpp \
\
				Types/Complex.cpp \
				Types/Real.cpp \
				Types/Polynomial/Polynomial_core.cpp \
				Types/Polynomial/Polynomial_eval.cpp \
				Types/Polynomial/Polynomial_free_ops.cpp \
				Types/Polynomial/Polynomial_io.cpp \
				Types/Polynomial/Polynomial_ops_addsub.cpp \
				Types/Polynomial/Polynomial_ops_divmod.cpp \
				Types/Polynomial/Polynomial_ops_mul.cpp \
				Types/Polynomial/Polynomial_pow.cpp \
				Types/Polynomial/Polynomial_solve.cpp \
\
				Visitors/BinaryOpVisitor.cpp \
				Visitors/UnaryOpVisitor.cpp \
\
				Nodes/BinaryOpNode.cpp \
				Nodes/UnaryOpNode.cpp \
				Nodes/MatrixNode.cpp \
				Nodes/ImaginaryNode.cpp \
				Nodes/VariableNode.cpp \
				Nodes/NumberNode.cpp \
				Nodes/FunctionCallNode.cpp \

################################################################################
#                                    COlORS                                    #
################################################################################

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
	$(1) 2> $@.log; \
	RESULT=$$?; \
	if [ $$RESULT -ne 0 ] || [ -s $@.log ]; then \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
	else  \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
	fi; \
	cat $@.log; \
	rm -f $@.log 2> /dev/null; \
	exit $$RESULT
endef

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

################################################################################
#                                   COMMANDS                                   #
################################################################################

all: $(OBJS_PATH) $(NAME)

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(NAME): COM_STRING = Linking
$(NAME): $(OBJS_PATH) $(OBJS)
	@$(call run_and_test, $(CXX) $(CXXFLAGS) -o $@ $(OBJS))

$(OBJS_PATH)%.o: COM_STRING = Compiling
$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	@mkdir -p $(dir $@)
	@$(call run_and_test, $(CXX) $(CXXFLAGS) -c $< -o $@)

clean: COM_STRING = Cleaning
clean:
	@$(call run_and_test, rm -rf $(OBJS_PATH))

fclean: COM_STRING = Cleaning
fclean: clean
	@$(call run_and_test, rm -f $(NAME))

re: fclean all

.PHONY: all clean fclean re"