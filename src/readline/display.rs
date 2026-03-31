use std::io::{self, Write};
use libc::{ioctl, winsize, TIOCGWINSZ, STDOUT_FILENO};

pub struct Display {
    pub prompt: String,
}

impl    Display {
    pub fn new(prompt: &str) -> Self
    {
        Display { prompt: prompt.to_string(), }
    }

    fn terminal_width() -> usize
    {
        let mut ws: winsize = unsafe { std::mem::zeroed() };
        unsafe { ioctl(STDOUT_FILENO, TIOCGWINSZ, &mut ws) };

        if ws.ws_col == 0 { 80 }
        else { ws.ws_col as usize }
    }

    fn count_lines(total_len: usize, width: usize) -> usize
    {
        if total_len == 0 { 1 }
        else { (total_len / width) + 1 }
    }

    pub fn render(&self, buffer: &[char], cursor: usize)
    {
        let width = Self::terminal_width();
        let total_len = self.prompt.len() + buffer.len();
        let lines = Self::count_lines(total_len, width);

        let mut output = String::new();

        for _ in 0..lines - 1
        {
            output.push_str("\x1b[1A");
        }
        output.push_str("\x1b[1G\x1b[0J");

        output.push_str(&self.prompt);
        for c in buffer
        {
            output.push(*c);
        }

        let cursor_abs = self.prompt.len() + cursor;
        let cursor_line = cursor_abs / width;
        let cursor_col = cursor_abs % width + 1;

        let current_line = (total_len) / width;
        if current_line > cursor_line
        {
            let diff = current_line - cursor_line;
            output.push_str(&format!("\x1b[{}A", diff));
        }

        output.push_str(&format!("\x1b[{}G", cursor_col));

        print!("{}", output);
        io::stdout().flush().unwrap();
    }

    pub fn newline(&self, buffer: &[char])
    {
        let width = Self::terminal_width();
        let total_len = self.prompt.len() + buffer.len();
        let lines = Self::count_lines(total_len, width);
        let current_line = total_len / width;
    
        let mut output = String::new();
        if current_line > 0
        {
            output.push_str(&format!("\x1b[{}B", lines - 1 - (total_len / width - current_line)));
        }
        output.push_str("\r\n");
        print!("{}", output);
        io::stdout().flush().unwrap();
    }
}
