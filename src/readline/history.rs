use std::fs::{File, OpenOptions};
use std::io::{BufRead, BufReader, Write};
use std::path::PathBuf;

pub struct History {
    entries:    Vec<String>,
    index:      usize,
    current:    String,
}

impl    History
{
    pub fn new() -> Self
    {
        let mut history  = History {
            entries:    Vec::new(),
            index:      0,
            current:    String::new(),
        };

        history.load();
        history.index = history.entries.len();

        history
    }

    fn path() -> PathBuf
    {
        let home = std::env::var("HOME").unwrap_or(String::from("/tmp"));
        PathBuf::from(home).join(".42sh_history")
    }

    fn load(&mut self)
    {
        let path = Self::path();

        if let Ok(file) = File::open(&path)
        {
            let reader = BufReader::new(file);
            for line in reader.lines()
            {
                if let Ok(entry) = line
                {
                    if  !entry.is_empty()
                    {
                        self.entries.push(entry);
                    }
                }
            }
        }
    }

    pub fn save(&self, entry: &str)
    {
        if entry.is_empty() { return; }

        let path = Self::path();

        if let Ok(mut file) = OpenOptions::new().append(true).create(true).open(&path)
        {
            writeln!(file, "{}", entry).unwrap();
        }
    }

    pub fn push(&mut self, entry: String)
    {
        if !entry.is_empty()
        {
            self.save(&entry);
            self.entries.push(entry);
            self.index = self.entries.len();
        }
    }

    pub fn prev(&mut self, current: &[char]) -> Option<&str>
    {
        if self.index == self.entries.len()
        {
            self.current = current.iter().collect();
        }
        if self.index > 0
        {
            self.index -= 1;
            Some(&self.entries[self.index])
        }
        else { None }
    }

    pub fn next(&mut self) -> Option<&str>
    {
        if self.index < self.entries.len()
        {
            self.index += 1;
        }
        if self.index == self.entries.len()
        {
            Some(&self.current)
        }
        else
        {
            Some(&self.entries[self.index])
        }
    }

	pub fn entries(&self) -> &Vec<String>
	{
		&self.entries
	}

    pub fn  get(&self, index: usize) -> Option<&String>
    {
        self.entries.get(index)
    }

    pub fn  len(&self) -> usize
    {
        self.entries.len()
    }
}
