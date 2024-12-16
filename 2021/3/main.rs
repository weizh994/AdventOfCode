use std::convert::TryInto;
use std::fs::File;
use std::io::{self, BufRead, BufReader};

fn main() -> io::Result<()> {
    let file = File::open("input")?;
    let reader = BufReader::new(file);
    let mut report: Vec<Vec<i32>> = Vec::new();
    for line in reader.lines() {
        let line = line?;
        let row: Vec<i32> = line
            .chars()
            .filter_map(|c| c.to_digit(10))
            .map(|n| n as i32)
            .collect();
        report.push(row);
    }
    let mut gamma = 0b0;
    for i in 0..report[0].len() {
        if i > 0 {
            gamma <<= 1;
        }
        let mut sum = 0;
        for j in 0..report.len() {
            sum += report[j][i];
        }
        if sum >= (report.len() / 2).try_into().unwrap() {
            gamma += 0b1;
        }
    }
    let mut epsilon = !gamma;
    let mask = (1 << report[0].len()) - 1;
    epsilon &= mask;
    let num = format!("{:0width$b}", epsilon, width = report[0].len());
    println!("Number: {}", gamma * epsilon);
    Ok(())
}
