use crate::readline::input::{read_action, Action};
use crate::readline::display::Display;
use crate::readline::history::History;
use std::io::{self, Write};

pub struct Editor {
    buffer:     Vec<char>,
    cursor:     usize,
    history:    History,
    display:    Display,
    kill_ring:  String,
}

impl    Editor {
    pub fn new(prompt: &str) -> Self
    {
        Editor {
            buffer:     Vec::new(),
            cursor:     0,
            history:    History::new(),
            display:    Display::new(prompt),
            kill_ring:  String::new(),
        }
    }

    fn  skip_spaces_forward(&mut self)
    {
        while self.cursor < self.buffer.len() && self.buffer[self.cursor] == ' '
        {
            self.cursor += 1;
        }
    }

    fn  skip_word_forward(&mut self)
    {
        while self.cursor < self.buffer.len() && self.buffer[self.cursor] != ' '
        {
            self.cursor += 1;
        }
    }

    fn  skip_spaces_backward(&mut self)
    {
        while self.cursor > 0 && self.buffer[self.cursor - 1] == ' '
        {
            self.cursor -= 1;
        }
    }

    fn  skip_word_backward(&mut self)
    {
        while self.cursor > 0 && self.buffer[self.cursor - 1] != ' '
        {
            self.cursor -= 1;
        }
    }

    fn  insert(&mut self, c: char)
    {
        self.buffer.insert(self.cursor, c);
        self.cursor += 1;
    }

    fn  backspace(&mut self)
    {
        if self.cursor > 0
        {
            self.cursor -= 1;
            self.buffer.remove(self.cursor);
        }
    }

    fn  move_left(&mut self)
    {
        if self.cursor > 0
        {
            self.cursor -= 1;
        }
    }

    fn  move_right(&mut self)
    {
        if self.cursor < self.buffer.len()
        {
            self.cursor += 1;
        }
    }

    fn  move_home(&mut self)
    {
        self.cursor = 0;
    }

    fn  move_end(&mut self)
    {
        self.cursor = self.buffer.len();
    }

    fn  clear_before(&mut self)
    {
        let killed: String = self.buffer[..self.cursor].iter().collect();
        self.kill_ring = killed;
        self.buffer.drain(..self.cursor);
        self.cursor = 0;
    }

    fn  clear_after(&mut self)
    {
        let killed: String = self.buffer[self.cursor..].iter().collect();
        self.kill_ring = killed;
        self.buffer.truncate(self.cursor);
    }

    fn  validate(&mut self) -> String
    {
        let line: String = self.buffer.iter().collect();
        self.history.push(line.clone());
        self.buffer.clear();
        self.cursor = 0;
        line
    }

    fn  catch_ctrl_d(&mut self) -> bool
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
        let start = self.cursor;
        
        self.skip_spaces_backward();
        self.skip_word_backward();

        let killed: String = self.buffer[self.cursor..start].iter().collect();
        self.kill_ring = killed;
        self.buffer.drain(self.cursor..start);
    }

    fn  catch_ctrl_y(&mut self)
    {
        for c in self.kill_ring.clone().chars()
        {
            self.insert(c);
        }
    }

    fn  catch_ctrl_t(&mut self)
    {
        if self.cursor > 2
        {
            self.buffer.swap(self.cursor - 2, self.cursor - 1)
        }
        else if self.cursor == 1 && self.buffer.len() >= 2
        {
            self.buffer.swap(0, 1);
            self.cursor += 1;
        }
    }

    fn  catch_ctrl_arrow_left(&mut self)
    {
        self.skip_spaces_backward();
        self.skip_word_backward();
    }
    
    fn  catch_ctrl_arrow_right(&mut self)
    {
        self.skip_spaces_forward();
        self.skip_word_forward();
    }

    fn  catch_alt_f(&mut self)
    {
        self.skip_spaces_forward();
        self.skip_word_forward();
    }

    fn  catch_alt_b(&mut self)
    {
        self.skip_spaces_backward();
        self.skip_word_backward();
    }

    fn  catch_alt_d(&mut self)
    {
        let start = self.cursor;
        self.skip_spaces_forward();
        self.skip_word_forward();
        self.buffer.drain(start..self.cursor);
        self.cursor = start;
    }

    fn  catch_alt_u(&mut self)
    {
        self.skip_spaces_forward();
        while self.cursor < self.buffer.len() && self.buffer[self.cursor] != ' '
        {
            self.buffer[self.cursor] = self.buffer[self.cursor].to_uppercase().next().unwrap();
            self.cursor += 1;
        }
    }

    fn  catch_alt_l(&mut self)
    {
        self.skip_spaces_forward();
        while self.cursor < self.buffer.len() && self.buffer[self.cursor] != ' '
        {
            self.buffer[self.cursor] = self.buffer[self.cursor].to_lowercase().next().unwrap();
            self.cursor += 1;
        }
    }

    fn  catch_alt_c(&mut self)
    {
        self.skip_spaces_forward();
        if self.cursor < self.buffer.len()
        {
            self.buffer[self.cursor] = self.buffer[self.cursor].to_uppercase().next().unwrap();
            self.cursor += 1;
        }
        while self.cursor < self.buffer.len() && self.buffer[self.cursor] != ' '
        {
            self.buffer[self.cursor] = self.buffer[self.cursor].to_lowercase().next().unwrap();
            self.cursor += 1;
        }
    }

    fn  catch_alt_t(&mut self)
    {
        let mut word_end2 = self.cursor;
        while word_end2 < self.buffer.len() && self.buffer[word_end2] != ' '
        {
            word_end2 += 1;
        }

        let mut word_start2 = word_end2;
        while word_start2 > 0 && self.buffer[word_start2 - 1] != ' '
        {
            word_start2 -= 1;
        }

        let mut word_end1 = word_start2;
        while word_end1 > 0 && self.buffer[word_end1 - 1] == ' '
        {
            word_end1 -= 1;
        }

        let mut word_start1 = word_end1;
        while word_start1 > 0 && self.buffer[word_start1 - 1] != ' '
        {
            word_start1 -= 1;
        }

        if word_start1 < word_end1 && word_start2 < word_end2
        {
            let word1:  Vec<char> = self.buffer[word_start1..word_end1].to_vec();
            let word2:  Vec<char> = self.buffer[word_start2..word_end2].to_vec();
        
            self.buffer.splice(word_start2..word_end2, word1);
            self.buffer.splice(word_start1..word_end1, word2);
            
            self.cursor = word_start2 + (word_end2 - word_start2);
        }
    }

    fn  catch_alt_hash(&mut self)
    {
        self.cursor = 0;
        self.buffer.insert(0, '#');
        self.cursor = self.buffer.len();
        self.display.render(&self.buffer, self.cursor);
        self.display.newline(&self.buffer);
        self.validate();
    }

    fn  catch_alt_dot(&mut self)
    {
        if let Some(last) = self.history.last()
        {
            let last_arg: String = last
                .split_whitespace()
                .last().unwrap_or("")
                .to_string();
        
            for c in last_arg.chars()
            {
                self.insert(c);
            }
        }
    }
    
    fn  history_prev(&mut self)
    {
        if let Some(entry) = self.history.prev(&self.buffer)
        {
            self.buffer = entry.chars().collect();
            self.cursor = self.buffer.len();
        }
    }

    fn  history_next(&mut self)
    {
        if let Some(entry) = self.history.next()
        {
            self.buffer = entry.chars().collect();
            self.cursor = self.buffer.len();
        }
    }

    pub fn  readline(&mut self) -> Option<String>
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
                Action::CtrlY       => self.catch_ctrl_y(),
                Action::CtrlT       => self.catch_ctrl_t(),
                Action::CtrlAR      => self.catch_ctrl_arrow_right(),
                Action::CtrlAL      => self.catch_ctrl_arrow_left(),
                Action::AltU        => self.catch_alt_u(),
                Action::AltL        => self.catch_alt_l(),
                Action::AltC        => self.catch_alt_c(),
                Action::AltT        => self.catch_alt_t(),
                Action::AltHash     => self.catch_alt_hash(),
                Action::AltDot      => self.catch_alt_dot(),
                Action::Unknown     => {}
            }
            self.display.render(&self.buffer, self.cursor);
        }
    }
}
