const matrix = [
    [1, 2, -3, 5],
    [2, -1, -1, 1],
    [3, 3, 4, 6],
];  
    
for (let k = 0; k < matrix.length; k++) {

    document.write((k + 1) + " - ПРОХОД" + "</br>" + "</br>");

    //!Вывод до привода к единице, И после зануления (на 2 итериации)
    print(matrix);

    //*выбор ведущего
    let max = k;
    let item;
    for (let i = k + 1; i < matrix[k].length - 1; i++) {
        if (Math.abs(matrix[i][k]) > Math.abs(matrix[max][k])) {max = i}
    }
        if (max !== k) {
        for(let i = 0; i < matrix[k].length; i++) {
            let temp = matrix[k][i];
            matrix[k][i] = matrix[max][i];
            matrix[max][i] = temp;
        }
    } 

    //!вывод после выбора ведущего
    print(matrix);



    const divisor = matrix[k][k];
    for (let j = k; j < matrix[k].length; j++) {
        matrix[k][j] /= divisor; //Делим всю первую строку на akk
    }

    //!вывод после привода к единице
    print(matrix);

    for (let i = k + 1; i < matrix.length; i++) { //цикл для строк
        const factor = matrix[i][k]; // элемент для зануления
        for (let j = k; j < matrix[i].length; j++) { //цикл для столбцов
        matrix[i][j] -= factor * matrix[k][j]; //зануляем элементы столбца
        }
    }
}

                                            //*Обратный ход
const solutions = new Array(matrix.length); 
for (let i = matrix.length - 1; i >= 0; i--) {
    solutions[i] = matrix[i][matrix[i].length - 1]; 
    for (let j = i + 1; j < matrix.length; j++) {
    solutions[i] -= matrix[i][j] * solutions[j];
    } 
}

                                            //*Результаты
document.write("РЕЗУЛЬТАТЫ" + "</br>")
for (let i = 0; i < solutions.length; i++){
    document.write("x" + (i+1) + "= " + solutions[i] + "</br>")
}



function print(arr) {
    for(let i = 0; i < matrix.length; i++) { 
        document.write(matrix[i].join("|") + "</br>");
    } document.writeln("</br>")
}