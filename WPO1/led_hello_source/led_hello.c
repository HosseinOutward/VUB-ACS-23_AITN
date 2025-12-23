#include "contiki.h"
#include "dev/leds.h"
#include "sys/etimer.h"
#include <stdio.h>
/*---------------------------------------------------------------------------*/
static struct etimer et;
static uint8_t counter;
/*---------------------------------------------------------------------------*//*---------------------------------------------------------------------------*/
PROCESS(led_hello, "LED HAL Example");
AUTOSTART_PROCESSES(&led_hello);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(led_hello, ev, data) // This should match the name given in PROCESS()
{
  PROCESS_BEGIN();

  /* Setup a periodic timer that expires after 1 seconds. */
  etimer_set(&et, CLOCK_SECOND);
  counter = 0;

  while(1) {
    PROCESS_YIELD();

    if(ev != PROCESS_EVENT_TIMER || data != &et)
      continue;

    // Switch based on counter value
    switch(counter % 20){
      case 0:
        printf("hello hello, everyone hello\n");
        break;
      case 7:
        leds_on(LEDS_ALL);
        break;
      case 14:
        leds_off(LEDS_ALL);
        break;
    }
    counter++;
    etimer_set(&et, CLOCK_SECOND);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

