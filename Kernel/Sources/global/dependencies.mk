DEP_INCLUDES=

DEP_LIBS= -larch
DEP_LIBS+= -lcore
DEP_LIBS+= -lio

DEP_MODULES = -L../arch/bin
DEP_MODULES += -L../core/bin
DEP_MODULES += -L../io/bin