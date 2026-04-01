const epsilon = 1e-10; //сравнимый ноль

function modifiedCholesky(A, b) {
    const n = A.length;

    const L = new Array(n); //создане матриц
    const D = new Array(n);

    for (let i = 0; i < n; i++) { //L - диагонльная 1
        L[i] = new Array(n).fill(0);
        L[i][i] = 1; 
    }

    for (let j = 0; j < n; j++) { //вычисление матриц D L
        let sumD = 0;
        for (let k = 0; k < j; k++) {
            sumD += L[j][k] * L[j][k] * D[k]; //вычисление накопителя для D  
        }
        D[j] = A[j][j] - sumD; //1 формула

        if (Math.abs(D[j]) < epsilon) {
            throw new Error(`Матрица - вырождена: D[${j}] = ${D[j]}  `); //2 формула
        }

        for (let i = j + 1; i < n; i++) { 
            let sumL = 0;
            for (let k = 0; k < j; k++) {//вычисление накопителя для L
                sumL += L[i][k] * L[j][k] * D[k];
            }
            L[i][j] = (A[i][j] - sumL) / D[j]; //3 формула
        }
    }

    const y = new Array(n);
    for (let i = 0; i < n; i++) {  
        let sum = 0;
        for (let j = 0; j < i; j++) {
            sum += L[i][j] * y[j]; //вычисление накопителя для y
        }
        y[i] = b[i] - sum; // 4 формула 
    }
    
    const z = new Array(n); //5 формула 
    for (let i = 0; i < n; i++) {
        z[i] = y[i] / D[i];
    }
    
    const x = new Array(n);
    for (let i = n - 1; i >= 0; i--) { //6 формула
        let sum = 0;
        for (let j = i + 1; j < n; j++) {
            sum += L[j][i] * x[j];
        }
        x[i] = z[i] - sum; 
    }
    return { solution: x, L: L, D: D, y: y, z: z };
}

const A = [
    [9, -2, 1, -1],
    [-2, 8, 2 ,1],
    [1, 2, 7, -1],
    [-1, 1, -1, 6]
];

// детерминант семетричность (проверка b = 0)

const b = [7, 9, 9, 5];

const result = modifiedCholesky(A, b);


document.write("</br>РЕШЕНИЕ СИСТЕМЫ:</br>");
for (let i = 0; i < result.solution.length; i++) {
    document.write("x" + (i+1) + " = " + result.solution[i].toFixed(6) + "</br>");
}