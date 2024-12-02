import { promises as fs } from 'fs';
import { report } from 'process';

async function readFileTo2DList(filePath: string): Promise<number[][]> {
    try {
        const data = await fs.readFile(filePath, 'utf-8');
        const rows: number[][] = data
            .split('\n') 
            .filter(line => line.trim() !== '') 
            .map(line => 
                line.trim()
                    .split(/\s+/)
                    .map(Number)
            );

        return rows;
    } catch (error) {
        console.error('Error reading file:', error);
        return [];
    }
}

async function isSafe(report: number[]): Promise<boolean> {
    const sum = report.reduce((acc, num) => acc + num, 0);
    const avg = sum / report.length;
    const increasing = report[0]<avg;
    for(let i = 0; i < report.length-1; i++) {
        if(increasing) {
            if(report[i] >= report[i+1]) {
                return false;
            }
            else if(report[i+1]-report[i] > 3) {return false;}
        }
        else {
            if(report[i] <= report[i+1]) {
                return false;
            }
            else if(report[i]-report[i+1] > 3) {return false;}
        }
    }
    return true;
}

async function safeReport(report: number[]): Promise<boolean> {
    if(await isSafe(report)) {
        return true;
    }
    for(let i = 0; i < report.length; i++) {
        let newReport = [...report];
        newReport.splice(i, 1);
        if(await isSafe(newReport)) {
            return true;
        }
    }
    return false;

}
async function main() {
    const filePath = 'input'; 
    const repoets = await readFileTo2DList(filePath);
    let answer: number = 0;

    for(let report of repoets) {
        if(await safeReport(report)) {
            answer++;
        }
    }
    console.log(answer);
}

main();