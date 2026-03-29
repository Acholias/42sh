use crate::readline::input::{read_action, Action};
use crate::readline::display::Display;
use crate::readline::history::History;

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

    fn catch_ctrl_d(&mut self)
    {
        if self.buffer.is_empty()
        {
            self.display.newline();
            std::process::exit(0);
        }
        else
        {
            if self.cursor < self.buffer.len()
            {
                self.buffer.remove(self.cursor);
            }
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

    pub fn read_line(&mut self) -> String
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
                    self.display.newline();
                    return self.validate();
                }
                Action::CTRLD       => self.catch_ctrl_d(),
                Action::MoveUp      => self.history_prev(),
                Action::MoveDown    => self.history_next(),
                Action::Unknown     => todo!()
            }
            self.display.render(&self.buffer, self.cursor);
        }
    }
}
