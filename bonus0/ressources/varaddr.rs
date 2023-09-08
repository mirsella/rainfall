use std::env;

fn main() {
    let var: Vec<String> = env::args().collect();
    println!("{}: {:p}", var[1], &env::var(&var[1]).unwrap());
}
