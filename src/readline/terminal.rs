// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   terminal.rs                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/04/20 14:37:32 by lumugot           #+#    #+#             //
//   Updated: 2026/04/20 14:37:32 by lumugot          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

use libc::{tcgetattr, tcsetattr, termios, STDIN_FILENO, TCSANOW};
use libc::{signal, SIGINT, SIG_IGN};
use std::mem;

pub struct RawMode {
    original:   termios,
}

impl    RawMode {
    pub fn enable() -> Self
    {
        let mut termios = unsafe { mem::zeroed::<termios>() };

        unsafe { tcgetattr(STDIN_FILENO, &mut termios) };

        let original = termios;

        termios.c_lflag &= !(libc::ICANON | libc::ECHO | libc::ISIG);

        termios.c_cc[libc::VMIN] = 1;
        termios.c_cc[libc::VTIME] = 0;

        unsafe { tcsetattr(STDIN_FILENO, TCSANOW, &termios) };

        unsafe { signal(SIGINT, SIG_IGN) };

        RawMode { original }
    }
}

impl Drop for RawMode {
    fn drop(&mut self)
    {
        unsafe { tcsetattr(STDIN_FILENO, TCSANOW, &self.original) };

        unsafe { signal(SIGINT, libc::SIG_DFL) };
    }
}
