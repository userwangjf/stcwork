

#include "bsp/config.h"
#include "shell/printk.h"


#if 1

static u8 mcu_strlen(const u8 *s)
{
	u8 len = 0;
	while (s[len] != '\0') len++;
	return len;
}

static u8 mcu_itoa(u32 value, u8 radix, u8 uppercase, u8 unsig,
	 u8 *buffer, u8 zero_pad)
{
	u8 *pbuffer = buffer;
	u8 negative = 0;
	u8 i, len;

	/* No support for unusual radixes. */
	if (radix > 16)
		return 0;

	if (value < 0 && !unsig) {
		negative = 1;
		value = -value;
	}

	/* This builds the string back to front ... */
	do {
		u8 digit = value % radix;
		*(pbuffer++) = (digit < 10 ? '0' + digit : (uppercase ? 'A' : 'a') + digit - 10);
		value /= radix;
	} while (value > 0);

	for (i = (pbuffer - buffer); i < zero_pad; i++)
		*(pbuffer++) = '0';

	if (negative)
		*(pbuffer++) = '-';

	*(pbuffer) = '\0';

	/* ... now we reverse it (could do it recursively but will
	 * conserve the stack space) */
	len = (pbuffer - buffer);
	for (i = 0; i < len / 2; i++) {
		char j = buffer[i];
		buffer[i] = buffer[len-i-1];
		buffer[len-i-1] = j;
	}

	return len;
}

struct mcu_buff {
	u8 *buffer, *pbuffer;
	u8 buffer_len;
};

static u8 _putc(u8 ch, struct mcu_buff *b)
{
	if ((u8)((b->pbuffer - b->buffer) + 1) >= b->buffer_len)
		return 0;
	*(b->pbuffer++) = ch;
	*(b->pbuffer) = '\0';
	return 1;
}

static u8 _puts(u8 *s, u8 len, struct mcu_buff *b)
{
	u8 i;

	if (b->buffer_len - (b->pbuffer - b->buffer) - 1 < len)
		len = b->buffer_len - (b->pbuffer - b->buffer) - 1;

	/* Copy to buffer */
	for (i = 0; i < len; i++)
		*(b->pbuffer++) = s[i];
	*(b->pbuffer) = '\0';

	return len;
}

u8 mcu_vsnprintf(u8 *buffer, u8 buffer_len, const u8 *fmt, va_list va)
{
	struct mcu_buff b;
	u8 bf[24];
	u8 ch;

	b.buffer = buffer;
	b.pbuffer = buffer;
	b.buffer_len = buffer_len;

	while ((ch=*(fmt++))) {
		if ((u8)((b.pbuffer - b.buffer) + 1) >= b.buffer_len)
			break;
		if (ch!='%')
			_putc(ch, &b);
		else {
			u8 zero_pad = 0;
			u8 *ptr;
			u8 len;

			ch=*(fmt++);

			/* Zero padding requested */
			if (ch=='0') {
				ch=*(fmt++);
				if (ch == '\0')
					goto end;
				if (ch >= '0' && ch <= '9')
					zero_pad = ch - '0';
				ch=*(fmt++);
			}

			switch (ch) {
				case 0:
					goto end;

				case 'u':
				case 'd':
					len = mcu_itoa(va_arg(va, u32), 10, 0, (ch=='u'), bf, zero_pad);
					_puts(bf, len, &b);
					break;

				case 'x':
				case 'X':
					len = mcu_itoa(va_arg(va, u32), 16, (ch=='X'), 1, bf, zero_pad);
					_puts(bf, len, &b);
					break;

				case 'c' :
					_putc((char)(va_arg(va, u8)), &b);
					break;

				case 's' :
					ptr = (u8*)va_arg(va, u8*);
					_puts(ptr, mcu_strlen(ptr), &b);
					break;

				default:
					_putc(ch, &b);
					break;
			}
		}
	}
end:
	return b.pbuffer - b.buffer;
}

u8 print_buf[128];
u8 printk(const u8 *fmt, ...)
{
	u8 ret;
	va_list va;
	while(Uart1_Busy());

	va_start(va, fmt);
	ret = mcu_vsnprintf(print_buf, 128, fmt, va);
	va_end(va);
	Uart1_Tx(print_buf);

	return ret;
}

#endif

