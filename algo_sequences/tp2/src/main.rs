

fn edit_distance_table<F, G, H>(w1: &Vec<char>,
                       w2: &Vec<char>,
                       del: F,
                       ins: G,
                       sub: H) -> Vec<Vec<usize>>
where
    F: Fn(char) -> usize,
    G: Fn(char) -> usize,
    H: Fn(char, char) -> usize
{
    

    let m = w1.len();
    let n = w2.len();
    let mut table = (0..(m+1))
        .map(|_i| (0..(n+1))
             .map(|_j| 0)
             .collect::<Vec<_>>())
        .collect::<Vec<_>>();


    table[0][0] = 0; // pour faire bonne mesure

    for i in 1..(m+1)
    {
        table[i][0] = table[i-1][0] + del(w1[i-1]);
    }

    for j in 1..(n+1)
    {
        table[0][j] = table[0][j-1] + ins(w2[j-1]);
    }

    for i in 1..(m+1)
    {
        for j in 1..(n+1)
        {
            table[i][j] =
                (table[i][j-1] + ins(w2[j-1]))
                .min(table[i-1][j] + del(w1[i-1]))
                .min(table[i-1][j-1] + sub(w1[i-1], w2[j-1]));
        }
    }

    
    table
}




fn edit_distance(w1: &Vec<char>,
                 w2: &Vec<char>) -> usize
{
    let del = |_: char| 1;
    let ins = |_: char| 1;
    let sub = |a: char, b: char| if a == b {0} else {1};
    
    let table = edit_distance_table(w1, w2, del, ins, sub);
    print_table(&table);
    table[table.len()-1][table[0].len()-1]
}




fn alignement_score(w1: &Vec<char>,
                    w2: &Vec<char>) -> usize
{
    let big_int = (w1.len()+w2.len())*200;
    let del = |_: char| 1;
    let ins = |_: char| 1;
    let sub = |a: char, b: char|
    {
        if a == b {0}
//        else if a == ' ' {0}
        else {1}
    };
    
    let table = edit_distance_table(w1, w2, del, ins, sub);
    print_table(&table);
    table[table.len()-1][table[0].len()-1]
}


fn print_table(table: &Vec<Vec<usize>>)
{
    for i in 0.. table[0].len()
    {
        for j in 0.. table.len()
        {
            print!("{} ", table[j][i]);
        }
        println!();
    }
}






fn main() {
    let w1 = "abrd".chars().collect::<Vec<char>>();
    let w2 = "abcd".chars().collect::<Vec<char>>();



    println!("{:?}\n{:?}", w1, w2);
    
    println!("edit distance: {}", edit_distance(&w1, &w2));
    println!("alignement score: {}", alignement_score(&w1, &w2));



    
}
