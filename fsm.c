#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "fsm_structs.h"
#include "state.h"

StateMachine *MakeStateMachine() {
  StateMachine *sm = (StateMachine *)malloc(sizeof(StateMachine));
  sm->pipeline = MakeStates();
  sm->cur_state = START;
  return sm;
}

int Step(StateMachine *sm) {
  StateName next = sm->pipeline[(int)sm->cur_state].action(sm);
  sm->cur_state = next;
  return 0;
}

void DeleteStateMachine(StateMachine *sm) {
  DeleteStates(sm->pipeline);
  free(sm);
}

int main() {
    FILE *input_file = fopen("D:\\c\\.vscode\\input.txt", "r");
    if (input_file == NULL) {
        printf("Error: this file doesn't exist\n");
        return 0;
    }

    StateMachine* sm = MakeStateMachine();
    uint32_t small_words_count = 0;
    char c;
    while (c != EOF) {
        c = fgetc(input_file);
        if ((c == ' ' || c == '\n' || c == '\t') == false && isalpha(c) == false
         && c != EOF) {

            while ((c == ' ' || c == '\n' || c == '\t') == false && c != EOF) {
                c = fgetc(input_file);
            }
        }
        sm->cur_char = c;
        if ((c == ' ' || c == '\n' || c == '\t') && sm->cur_state == SMALL_WORD) {
            small_words_count++;
        }
        if (sm->cur_state == BIG_WORD) {
            while ((c == ' ' || c == '\n' || c == '\t') == false && c != EOF) {
                c = fgetc(input_file);
            }
            if (c == EOF) {
                sm->cur_state = FINISH;
            }
        }
        if (sm->cur_state == FINISH) {
            printf("Task done, word count: %d", small_words_count);
            break;
        }
        
    }
    printf("Task done, word count: %d", small_words_count);
    DeleteStateMachine(sm);
    fclose(input_file);
    return 0;
}