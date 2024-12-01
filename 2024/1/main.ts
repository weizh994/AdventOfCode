import * as fs from 'fs';

// Read the file synchronously
const data = fs.readFileSync('input', 'utf-8');

// Split the file into lines or process it directly
const lines = data.split('\n').filter(line => line.trim() !== '');

    // Initialize two arrays to store the columns
    const leftColumn: number[] = [];
    const rightColumn: number[] = [];

    // Process each line
    for (const line of lines) {
        const [left, right] = line.trim().split(/\s+/).map(Number);
        leftColumn.push(left);
        rightColumn.push(right);
    }
let answer: number = 0;

// Question 1
// leftColumn.sort();
// rightColumn.sort();
// for(let i = 0; i < leftColumn.length; i++) {
//     answer += Math.abs(leftColumn[i] - rightColumn[i]);
// }

// Question 2
const freq = new Map<number, number>();
for(let num of rightColumn) {
    freq.set(num, (freq.get(num) || 0) + 1);
}
for(let num of leftColumn) {
    answer += num*(freq.get(num) || 0);
}

console.log(answer);
