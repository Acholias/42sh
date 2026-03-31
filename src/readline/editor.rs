use crate::readline::input::{read_action, Action};
use crate::readline::display::Display;
use crate::readline::history::History;
use std::io::{self, Write};

pub struct Editor {
    buffer:     Vec<char>,
    cursor:     usize,
    history:    History,
    display:    Display,
}

impl    Editor {
    pub fn new(prompt: &str) -> Self
    {
        Editor {
            buffer:     Vec::new(),
            cursor:     0,
            history:    History::new(),
            display:    Display::new(prompt),
        }
    }

    fn insert(&mut self, c: char)
    {
        self.buffer.insert(self.cursor, c);
        self.cursor += 1;
    }

    fn backspace(&mut self)
    {
        if self.cursor > 0
        {
            self.cursor -= 1;
            self.buffer.remove(self.cursor);
        }
    }

    fn move_left(&mut self)
    {
        if self.cursor > 0
        {
            self.cursor -= 1;
        }
    }

    fn move_right(&mut self)
    {
        if self.cursor < self.buffer.len()
        {
            self.cursor += 1;
        }
    }

    fn move_home(&mut self)
    {
        self.cursor = 0;
    }

    fn move_end(&mut self)
    {
        self.cursor = self.buffer.len();
    }

    fn clear_before(&mut self)
    {
        self.buffer.drain(..self.cursor);
        self.cursor = 0;
    }

    fn clear_after(&mut self)
    {
        self.buffer.truncate(self.cursor);
    }

    fn validate(&mut self) -> String
    {
        let line: String = self.buffer.iter().collect();
        self.history.push(line.clone());
        self.buffer.clear();
        self.cursor = 0;
        line
    }

    fn catch_ctrl_d(&mut self) -> bool
    {
        if self.buffer.is_empty()
        {
            self.display.newline(&self.buffer);
            true
        }
        else
        {
            if self.cursor < self.buffer.len()
            {
                self.buffer.remove(self.cursor);
            }
            false
        }
    }

    fn  catch_ctrl_c(&mut self)
    {
        println!("^C");
        io::stdout().flush().unwrap();
        self.buffer.clear();
        self.cursor = 0;
        self.display.render(&self.buffer, self.cursor);
    }

    fn  catch_ctrl_l(&mut self)
    {
        print!("\x1b[2J\x1b[H");
        self.display.render(&self.buffer, self.cursor);
    }

    fn  catch_ctrl_w(&mut self)
    {
        while self.cursor > 0 && self.buffer[self.cursor - 1] == ' '
        {
            self.cursor -= 1;
            self.buffer.remove(self.cursor);
        }
        while self.cursor > 0 && self.buffer[self.cursor - 1] != ' '
        {
            self.cursor -= 1;
            self.buffer.remove(self.cursor);
        }
    }

    fn  catch_alt_f(&mut self)
    {
        while self.cursor < self.buffer.len() && self.buffer[self.cursor - 1] == ' '
        {
           self.cursor += 1; 
        }
        while self.cursor < self.buffer.len() && self.buffer[self.cursor - 1] != ' '
        {
            self.cursor += 1;
        }
    }

    fn catch_alt_b(&mut self)
    {
        while self.cursor > 0 && self.buffer[self.cursor - 1] == ' '
        {
            self.cursor -= 1;
        }
        while self.cursor > 0 && self.buffer[self.cursor - 1] != ' '
        {
            self.cursor -= 1;
        }
    }

    fn catch_alt_d(&mut self)
    {
        while self.cursor < self.buffer.len() && self.buffer[self.cursor] == ' '
        {
            self.buffer.remove(self.cursor);
        }
        while self.cursor < self.buffer.len() && self.buffer[self.cursor] != ' '
        {
            self.buffer.remove(self.cursor);
        }
    }

    fn history_prev(&mut self)
    {
        if let Some(entry) = self.history.prev(&self.buffer)
        {
            self.buffer = entry.chars().collect();
            self.cursor = self.buffer.len();
        }
    }

    fn history_next(&mut self)
    {
        if let Some(entry) = self.history.next()
        {
            self.buffer = entry.chars().collect();
            self.cursor = self.buffer.len();
        }
    }

    pub fn read_line(&mut self) -> Option<String>
    {
        self.display.render(&self.buffer, self.cursor);

        loop
        {
            match read_action()
            {
                Action::Char(c)     => self.insert(c),
                Action::Backspace   => self.backspace(),
                Action::MoveLeft    => self.move_left(),
                Action::MoveRight   => self.move_right(),
                Action::Home        => self.move_home(),
                Action::End         => self.move_end(),
                Action::Clear       => self.clear_before(),
                Action::ClearAfter  => self.clear_after(),
                Action::Enter       => { 
                    self.display.newline(&self.buffer);
                    return Some(self.validate());
                }
                Action::CtrlD       => if self.catch_ctrl_d() { return None }
                Action::CtrlC       => self.catch_ctrl_c(),
                Action::CtrlL       => self.catch_ctrl_l(),
                Action::CtrlW       => self.catch_ctrl_w(),
                Action::MoveUp      => self.history_prev(),
                Action::MoveDown    => self.history_next(),
                Action::AltF        => self.catch_alt_f(), 
                Action::AltB        => self.catch_alt_b(),
                Action::AltD        => self.catch_alt_d(),
                Action::Unknown     => {}
            }
            self.display.render(&self.buffer, self.cursor);
        }
    }
}
