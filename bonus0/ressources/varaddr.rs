use std::env::{args, var};

fn main() {
    println!("{}: {:p}", args().nth(1).unwrap(), &var(args().nth(1).unwrap()).unwrap());
}
