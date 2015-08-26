#include <Ts206.h>

Ts206 lcd(10, 9, 7);
// data, wr, cs

void setup()
{
	int i;
	lcd.begin();
	lcd.disp(1, 'H');
	lcd.disp(2, 'e');
	lcd.disp(3, 'l');
	lcd.disp(4, 'l');
	lcd.disp(5, 'o');
	lcd.disp(6, ' ');
	lcd.disp(7, '2');
	lcd.disp(8, '0');
	lcd.disp(9, '6');
}
void loop()
{

}
