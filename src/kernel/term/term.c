#include <term/term.h>

struct limine_terminal *terminal;

lock_t nept_term_write_char;

void term_write_char(const char ch)
{
    spinlock_lock(nept_term_write_char);
    char str[2] = {ch, 0};
    terminal_request.response->write(terminal, str, 1);
    if (ch == '\b')
    {
        terminal_request.response->write(terminal, " ", 1);
        terminal_request.response->write(terminal, str, 1);
    }
    spinlock_unlock(nept_term_write_char);
}

lock_t nept_term_write_str;

void term_write_str(const char* str, size_t len)
{
    spinlock_lock(nept_term_write_str);
    terminal_request.response->write(terminal, str, len);
    spinlock_unlock(nept_term_write_str);
}
void term_init()
{
    /* Checks if we have a terminal, if not just panic the system */
    if (terminal_request.response == NULL || terminal_request.response->terminal_count < 1)
    {
        panic("No Limine terminal found, system halted");
    }

    // nlog_info("Limine Terminal Initialized\n");
    nlog_info("[TERMINAL] >> Limine Terminal Initialized\n");
}