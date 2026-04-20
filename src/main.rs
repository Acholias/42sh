// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.rs                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: lumugot <lumugot@42angouleme.fr>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/04/20 14:55:21 by lumugot           #+#    #+#             //
//   Updated: 2026/04/20 14:55:22 by lumugot          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

mod readline;
use readline::terminal::RawMode;
use readline::editor::Editor;

fn main()
{
    let _raw = RawMode::enable();
    let mut editor = Editor::new("42sh> ");

    loop
    {
        match editor.readline()
        {
            Some(line)  =>  println!("Line catch with read_line : {}", line),
            None        => break,
        }
    }
}
