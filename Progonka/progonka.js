function progonka(a, b, c, d) {
    const n = d.length;

    const alpha = new Array(n);
    const beta = new Array(n);
    
    alpha[0] = -c[0] / b[0];
    beta[0] = d[0] / b[0];
    
    for (let i = 1; i < n - 1; i++) {
        const deno = b[i] + a[i] * alpha[i - 1];
        alpha[i] = -c[i] / deno;
        beta[i] = (d[i] - a[i] * beta[i - 1]) / deno;
    }

    deno = b[4] + a[4] * alpha[4 - 1]
    beta[4] = (d[4] - a[4] * beta[4 - 1]) / deno;

    //!обратный ход
    const x = new Array(n);
    x[n - 1] = beta[4];
    
    for (let i = n - 2; i >= 0; i--) {
        x[i] = alpha[i] * x[i + 1] + beta[i];
    }

    for (let i = 0; i < beta.length; i++) {
        document.write(beta[i] + "</br>")
        document.write(alpha[i] + "</br>")
        document.write("</br>")
    }
    
    return x;
}

                //! моя матрица 
const a = [0, -1, -1, -1, -1];   // нижняя диагональ  
const b = [8, 8, 8, 8, 8];   // главная диагональ
const c = [1, 1, 1, 1,0];   // верхняя диагональ  
const d = [32, 27, 20, 10, 70];   // правые части

                //! другой тест
// const a = [0, -1, 7, 4, -5];   // нижняя диагональ  
// const b = [8, 5, -5, 7, 8];   // главная диагональ
// const c = [-2, 3, -9, 9,0];   // верхняя диагональ  
// const d = [-7, 6, 9, -8, 5];   // правые части

const solution = progonka(a, b, c, d);

document.write("РЕЗУЛЬТАТЫ" + "</br>")
for (let i = 0; i < solution.length; i++){
    document.write("x" + (i+1) + "= " + solution[i] + "</br>")
}