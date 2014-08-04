/**
 * @file ND_Timer.cpp
 * @author Adrián Arroyo Calle
 * @brief Timer x86
 * */

#include <ND_Timer.hpp>
#include <ND_Ports.hpp>
#include <ND_Screen.hpp>
#include <ND_IRQ.hpp>

int ND_TIMER_TICKS=0;

void ND::Timer::Phase(unsigned int hz)
{
	unsigned int divisor=1193180/hz;
    // Send the command byte.
	ND::Ports::OutputB(0x43,0x36);
    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   // Send the frequency divisor.
	ND::Ports::OutputB(0x40, (uint8_t)(divisor & 0xFF) );
	ND::Ports::OutputB(0x40, (uint8_t)((divisor>>8) & 0xFF) );
}

void ND::Timer::Wait(int ticks)
{
	unsigned long eticks;
	eticks=ND_TIMER_TICKS+ticks;
	while(ND_TIMER_TICKS < eticks)
	{
    }
}
void ND::Timer::Setup()
{
	ND::Screen::SetColor(ND_SIDE_FOREGROUND, ND_COLOR_BLACK);
	ND::Screen::PutString("\nSetup timer...");

	ND_IRQ_InstallHandler(0,&ND_Timer_Handler);

	ND::Screen::SetColor(ND_SIDE_FOREGROUND,ND_COLOR_GREEN);
	ND::Screen::PutString("done");
}
extern "C"
void ND_Timer_Handler(struct regs* r)
{
	ND_TIMER_TICKS++;
	if(ND_TIMER_TICKS % 18 ==0)//100
	{
		ND::Screen::SetColor(ND_SIDE_FOREGROUND,ND_COLOR_BROWN);
		ND::Screen::PutString("\nOne more second");
	}else{
		ND::Screen::PutString("\nSomething strange");
	}
}
