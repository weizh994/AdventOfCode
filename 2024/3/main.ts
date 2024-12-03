import * as fs from 'fs';

function matchMulPatterns(input: string): number {
    // 定义正则表达式，匹配 mul(X,Y) 格式，X 和 Y 都是数字
    const pattern = /mul\(\d+,\d+\)/g;

    // 使用正则表达式匹配所有符合条件的子串
    const matches = input.match(pattern);

    let result: number = 0;
    if (!matches) {
        return result;
    }   
    for (const match of matches) {
        // 从匹配的子串中提取两个数字
        const [x, y] = match
            .slice(4, -1) // 去掉 mul( 和 ) 部分
            .split(',') // 用逗号分隔
            .map(Number); // 转换为数字

        // 计算乘积
        const product = x * y;
        result+=product;
        
    }
    return result;
}

function splitByDelimiters(input: string, delimiters: string[]): string[] {
    // 转义分隔符中的特殊字符
    const escapedDelimiters = delimiters.map(delimiter =>
        delimiter.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&')
    );

    // 构造正则表达式，将分隔符用 | 拼接
    const pattern = new RegExp(`(${escapedDelimiters.join('|')})`, 'g');

    // 使用正则表达式分割并保留分隔符
    const parts = input.split(pattern);

    // 返回分割后的数组
    return parts;
}

const data = fs.readFileSync('input', 'utf-8');
const delimiters = ["don't()", "do()"];
const results = splitByDelimiters(data, delimiters);
let flag: boolean = true;
let answer: number = 0;
for (const result of results) {
    if (result === "don't()") {
        flag = false;
    }
    else if(result === "do()") {
        flag = true;
    }
    if(flag) {
        answer += matchMulPatterns(result);
    }
}
console.log(answer);