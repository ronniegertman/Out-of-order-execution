/* 046267 Computer Architecture - HW #3 */
/* Implementation (skeleton)  for the dataflow statistics calculator */

#include "dflow_calc.h"

struct node{
    unsigned int parent1;
    unsigned int parent2;
    unsigned int latency;
    unsigned int depth;
};

struct tree{
    struct node* commands;
    int* registers;
};

ProgCtx analyzeProg(const unsigned int opsLatency[], const InstInfo progTrace[], unsigned int numOfInsts) {
    struct node* commands = (struct node*)malloc(numOfInsts * sizeof(struct  node));
    if(commands == NULL){
        return PROG_CTX_NULL;
    }
    int* registers = (int*)malloc(32 * sizeof(int));
    if (registers == NULL){
        free(commands);
        return PROG_CTX_NULL;
    }

    // setting all register dependencies to none
    for (int i=0; i<32; i++){
        registers[i] = -1;
    }

    for (int i=0; i<numOfInsts; i++){
        // saving the command's latency
        commands[i].latency = opsLatency[progTrace[i].opcode];

        // finding the registers the command is dependent on
        int reg_dep1 = progTrace[i].src1Idx;
        int reg_dep2 = progTrace[i].src2Idx;
    
        // finding the parent command of each of the registers above
        int parent1_index = registers[reg_dep1];
        int parent2_index = registers[reg_dep2];

        // keeping each parent index for the command
        commands[i].parent1 = parent1_index;
        commands[i].parent2 = parent2_index;

        // updating the register array according to the new dependency the command had set
        int new_dependency_register = progTrace[i].dstIdx;
        registers[new_dependency_register] = i;

        // calculating the current depth of the command
        int total_depth_p1 = commands[i].parent1 == -1 ? 0 : (commands[parent1_index].depth + commands[parent1_index].latency);
        int total_depth_p2 = commands[i].parent2 == -1 ? 0 : (commands[parent2_index].depth + commands[parent2_index].latency);
        commands[i].depth = total_depth_p1 >= total_depth_p2 ? total_depth_p1 : total_depth_p2;
    }

    struct tree* prog_ctx = (struct tree*)malloc(sizeof(struct tree));
    if (prog_ctx == NULL){
        free(commands);
        free(registers);
        return PROG_CTX_NULL;
    }

    prog_ctx->commands = commands;
    prog_ctx->registers = registers;
    return prog_ctx;
   
}

void freeProgCtx(ProgCtx ctx) {
}

int getInstDepth(ProgCtx ctx, unsigned int theInst) {
    return -1;
}

int getInstDeps(ProgCtx ctx, unsigned int theInst, int *src1DepInst, int *src2DepInst) {
    return -1;
}

int getProgDepth(ProgCtx ctx) {
    return 0;
}


