function cholesky(A, b) {
    const n = A.length;
    
 
    const L = new Array(n);
    for (let i = 0; i < n; i++) {
        L[i] = new Array(n).fill(0);
    }
 
    for (let i = 0; i < n; i++) {
 
        let sum = 0;
        for (let k = 0; k < i; k++) {
            sum += L[i][k] * L[i][k];
        }
        L[i][i] = Math.sqrt(A[i][i] - sum);
        
        for (let j = i + 1; j < n; j++) {
            sum = 0;
            for (let k = 0; k < i; k++) {
                sum += L[j][k] * L[i][k];
            }
            L[j][i] = (A[j][i] - sum) / L[i][i];
        }
    }

    const y = new Array(n);
    for (let i = 0; i < n; i++) {
        let sum = 0;
        for (let j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }
    

    const x = new Array(n);
    for (let i = n - 1; i >= 0; i--) {
        let sum = 0;
        for (let j = i + 1; j < n; j++) {
            sum += L[j][i] * x[j];
        }
        x[i] = (y[i] - sum) / L[i][i];
    }
    
    return { solution: x, L: L, y: y };
}

const A = [
    [31,15,10],
    [15,25,5],
    [10,5,42]
];

const b = [108.3, 92, 171]

const result = cholesky(A, b);

document.write("МАТРИЦА L:" + "</br>");
for (let i = 0; i < result.L.length; i++) {
    document.write(result.L[i].map(num => num.toFixed(4)).join(" | ") + "</br>");
}

document.write("</br>ПРОМЕЖУТОЧНЫЙ ВЕКТОР y:" + "</br>");
for (let i = 0; i < result.y.length; i++) {
    document.write("y" + (i+1) + "= " + result.y[i].toFixed(6) + "</br>");
}

document.write("</br>РЕЗУЛЬТАТЫ:" + "</br>");
for (let i = 0; i < result.solution.length; i++) {
    document.write("x" + (i+1) + "= " + result.solution[i].toFixed(6) + "</br>");
}

// // Проверка решения
// document.write("</br>ПРОВЕРКА A*x = b:" + "</br>");
// for (let i = 0; i < A.length; i++) {
//     let sum = 0;
//     for (let j = 0; j < A[i].length; j++) {
//         sum += A[i][j] * result.solution[j];
//     }
//     document.write("Уравнение " + (i+1) + ": " + sum.toFixed(2) + " = " + b[i] + "</br>");
// }