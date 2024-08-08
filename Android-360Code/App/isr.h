#ifndef    _ISR_H
#define    _ISR_H
void Delay_MS(unsigned int t);
void Delay_10MS(unsigned int t);
void start_pwm(void);
void stop_pwm(void);
void sound(void);
void out_pulse(void);
void water_count(void);
void timer0_comp_isr(void);
void timer1_compc_isr(void);
void timer2_comp_isr(void);
void timer2_ovf_isr(void);
void timer3_compc_isr(void);
void timer3_ovf_isr(void);
void adc_isr(void);
#endif


