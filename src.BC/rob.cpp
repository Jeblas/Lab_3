#include <stdio.h>
#include <assert.h>

#include "rob.h"


extern int32_t NUM_ROB_ENTRIES;

/////////////////////////////////////////////////////////////
// Init function initializes the ROB
/////////////////////////////////////////////////////////////

ROB* ROB_init(void){
  int ii;
  ROB *t = (ROB *) calloc (1, sizeof (ROB));
  for(ii=0; ii<MAX_ROB_ENTRIES; ii++){
    t->ROB_Entries[ii].valid=false;
    t->ROB_Entries[ii].ready=false;
  }
  t->head_ptr=0;
  t->tail_ptr=0;
  return t;
}

/////////////////////////////////////////////////////////////
// Print State
/////////////////////////////////////////////////////////////
void ROB_print_state(ROB *t){
 int ii = 0;
  printf("Printing ROB \n");
  printf("Entry  Inst   Valid   ready\n");
  for(ii = 0; ii < NUM_ROB_ENTRIES; ii++) {
    printf("%5d ::  %d\t", ii, (int)t->ROB_Entries[ii].inst.inst_num);
    printf(" %5d\t", t->ROB_Entries[ii].valid);
    printf(" %5d\n", t->ROB_Entries[ii].ready);
  }
  printf("\n");
}

/////////////////////////////////////////////////////////////
//------- DO NOT CHANGE THE CODE ABOVE THIS LINE -----------
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
// If there is space in ROB return true, else false
/////////////////////////////////////////////////////////////

bool ROB_check_space(ROB *t){
    //std::cout << "ROB SPACE? = "<<!(t->ROB_Entries[t->tail_ptr].valid) << std::endl;
    return !(t->ROB_Entries[t->tail_ptr].valid);
}

/////////////////////////////////////////////////////////////
// insert entry at tail, increment tail (do check_space first)
/////////////////////////////////////////////////////////////

int ROB_insert(ROB *t, Inst_Info inst){
    int return_value = - 1;
    if (ROB_check_space(t)) {
        

        return_value = t->tail_ptr;

        t->ROB_Entries[t->tail_ptr].inst = inst;
        t->ROB_Entries[t->tail_ptr].valid = true;
        t->ROB_Entries[t->tail_ptr].ready = false;

        t->ROB_Entries[t->tail_ptr].inst.dr_tag = t->tail_ptr;

        if (t->tail_ptr == NUM_ROB_ENTRIES - 1) {
            t->tail_ptr = 0;
        } else {
            ++(t->tail_ptr);
        }
    }
    return return_value;
}

/////////////////////////////////////////////////////////////
// Once an instruction finishes execution, mark rob entry as done
/////////////////////////////////////////////////////////////

void ROB_mark_ready(ROB *t, Inst_Info inst){
    for (int ii = 0; ii < MAX_ROB_ENTRIES; ++ii) {
        if (t->ROB_Entries[ii].inst.inst_num == inst.inst_num
            && t->ROB_Entries[ii].valid == true) {
            t->ROB_Entries[ii].ready = true;
            return; // expecting inst_num to be a unique identifier
	}
    } 
}

/////////////////////////////////////////////////////////////
// Find whether the prf-rob entry is ready
/////////////////////////////////////////////////////////////

bool ROB_check_ready(ROB *t, int tag){
    // Might be wrong double check with someone
    return t->ROB_Entries[tag].ready;
}


/////////////////////////////////////////////////////////////
// Check if the oldest ROB entry is ready for commit
/////////////////////////////////////////////////////////////

bool ROB_check_head(ROB *t){
    return t->ROB_Entries[t->head_ptr].ready;
}

/////////////////////////////////////////////////////////////
// Remove oldest entry from ROB (after ROB_check_head)
/////////////////////////////////////////////////////////////

Inst_Info ROB_remove_head(ROB *t){
    int old_head = t->head_ptr;
    if (ROB_check_head(t)) {
        t->ROB_Entries[old_head].valid = false;

        if (t->head_ptr == NUM_ROB_ENTRIES - 1) {
            t->head_ptr = 0;
        } else {
            ++(t->head_ptr);
        }  

        return t->ROB_Entries[old_head].inst;
    }
    //TODO Figure out what to return
    //return; 
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
