use std::io::{self, Write};

pub struct Display {
    pub prompt: String,
}

impl    Display {
    pub fn new(prompt: &str) -> Self
    {
        Display { prompt: prompt.to_string(), }
    }

    pub fn render(&self, buffer: &[char], cursor: usize)
    {
        let mut output = String::new();

        output.push_str("\x1b[2K\x1b[1G");
        output.push_str(&self.prompt);

        for c in buffer { output.push(*c); }
    
        let cursor_pos = cursor + self.prompt.len() + 1;
        output.push_str(&format!("\x1b[{}G", cursor_pos));

        print!("{}", output);
        io::stdout().flush().unwrap();
    }

    pub fn newline(&self)
    {
        println!();
        io::stdout().flush().unwrap();
    }
}
