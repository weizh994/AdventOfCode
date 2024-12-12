use std::fs::File;
use std::io::{self, BufRead, BufReader};

fn main() -> io::Result<()> {
    let path = "input";

    let file = File::open(&path)?;
    let reader = BufReader::new(file);

    let mut orders: Vec<(String, i32)> = Vec::new();
    for line in reader.lines() {
        let line = line?;
        let mut parts = line.split_whitespace();
        if let (Some(command), Some(value)) = (parts.next(), parts.next()) {
            if let Ok(value) = value.parse::<i32>() {
                orders.push((command.to_string(), value));
            }
        }
    }

    let mut pos = (0, 0);
    for (command, value) in &orders {
        if command == "forward" {
            pos.1 += value;
        } else if command == "down" {
            pos.0 += value;
        } else if command == "up" {
            pos.0 -= value;
        } else {
            println!("Command: {}, Value: {}", command, value);
        }
    }
    println!("Question 1: {}", pos.0 * pos.1);
    let mut aim = 0;
    let mut pos = (0, 0);
    for (command, value) in &orders {
        if command == "forward" {
            pos.0 += value;
            pos.1 += value * aim;
        } else if command == "down" {
            aim += value;
        } else if command == "up" {
            aim -= value;
        } else {
            println!("Command: {}, Value: {}", command, value);
        }
    }
    println!("Question 2: {}", pos.0 * pos.1);
    Ok(())
}
