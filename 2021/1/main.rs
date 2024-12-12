use std::fs::File;
use std::io::{self, BufRead, BufReader};

fn main() -> io::Result<()> {
    let file = File::open("input")?;
    let reader = BufReader::new(file);

    let mut numbers: Vec<i32> = Vec::new();
    let mut result = 0;
    let mut prev = 0;
    for (index, line) in reader.lines().enumerate() {
        let line = line?;
        if line.trim().is_empty() {
            continue;
        }
        match line.trim().parse::<i32>() {
            Ok(num) => {
                if index == 0 {
                    prev = num;
                } else if num > prev {
                    result += 1;
                }
                prev = num;
                numbers.push(num);
            }
            Err(e) => eprintln!("row {} cannot be int: '{}', ERROR: {}", index + 1, line, e),
        }
    }
    println!("Question 1: {}", result);
    let mut prev = 0;
    let mut curr = 0;
    let mut result = 0;
    for index in 0..numbers.len() {
        if index < 3 {
            prev += numbers[index];
        } else {
            curr = prev - numbers[index - 3] + numbers[index];
            if curr > prev {
                result += 1;
            }
            prev = curr;
        }
    }
    println!("Question 2: {}", result);
    Ok(())
}
