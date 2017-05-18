use std::string;

mod nations;
mod sports;
mod parts;

const SIZE: usize = 80;

struct Nation<'a> {
    name: &'a str,
}

struct Participant<'a> {
    name: &'a str,
}

struct Sport<'a> {
    name: &'a str,
}

fn main() {
    let nations: [Nation; 20];
    let parts:   [Participant; 20];
    let sport:   [Sport; 20];

    // These two strings are examples of &str type string,
    //  These strings are STACK allocated.
    let name = "This is the best day I have had in my entire life.!";

    let multiline = "\nTo write a multiline \n\
                      properly I have to to escape the newline\n \
                      character and the spaces. \n";

    // Here is an example of a HEAP - allocated string
    let name2 = "Jonas johan solsvik".to_string();
    // It is possible to convert to a &str type string
    let name3 = &name2;
    // It is possible to convert back to String
    let name4 = name3.to_string();

    nations::run(multiline);
    sports::run();
    parts::run();
}
