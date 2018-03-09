#ifndef TRANSMISSION_H
#define TRANSMISSION_H

struct transmission{

  char sender,receiver;
  int start_time,duration,reach_target_time;        //duration sender ile receiver arasindaki sure , reach_target_time = start_time+ duration
  int end_time_of_emitting;
  int current_time;
  int is_start,is_end;

}typedef t;
#endif

