use std::io::{self, BufReader};
use std::io::prelude::*;
use std::fs::File;


/// to display the matrixes
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

/// used in q3
fn read(file_name: &str) -> io::Result<Vec<char>>
{
    let f = File::open(file_name)?;
    let mut buff = BufReader::new(f);
    let mut s = String::new();
    buff.read_to_string(&mut s)?;
    Ok(s.chars().collect())
}

/// used in q4
fn read_parag(file_name: &str) -> io::Result<Vec<Vec<char>>>
{
    let f = File::open(file_name)?;
    let mut buff = BufReader::new(f);
    let mut s = String::new();
    buff.read_to_string(&mut s)?;

    Ok(s.lines().map(|line| line.chars().collect()).collect())
}





/// generate the matrix
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




/// gives the edit discance of two chains
fn edit_distance(w1: &Vec<char>,
                 w2: &Vec<char>) -> usize
{
    let del = |_: char| 1;
    let ins = |_: char| 1;
    let sub = |a: char, b: char| if a == b {0} else {1};
    
    let table = edit_distance_table(w1, w2, del, ins, sub);
//    print_table(&table);
    table[table.len()-1][table[0].len()-1]
}


/// used in q3: return the best alignement between two chains
fn best_align(w1: &Vec<char>,
              w2: &Vec<char>) -> (Vec<char>, Vec<char>)
{
    let del = |_: char| 1;
    let ins = |_: char| 1;
    let sub = |a: char, b: char| if a == b {0} else {1};

    let table = edit_distance_table(w1, w2, del, ins, sub);


    let mut i = table.len() - 1;
    let mut j = table[0].len() - 1;

    let mut walign1 = vec![];
    let mut walign2 = vec![];
            
    
    while i != 0 && j != 0
    {
        let min = table[i][j-1]
            .min(table[i-1][j])
            .min(table[i-1][j-1]);
        
        if table[i][j-1] == min
        {
            walign1.insert(0, '_');
            walign2.insert(0, w2[j-1]);
            j -= 1;
        }
        else if table[i-1][j] == min
        {
            walign1.insert(0, w1[i-1]);
            walign2.insert(0, '_');
            i -= 1;
        }
        else if table[i-1][j-1] == table[i][j]
        {
            walign1.insert(0, w1[i-1]);
            walign2.insert(0, w2[j-1]);
            i -= 1;
            j -= 1;
        }
        else
        {
            walign1.insert(0, '_');
            walign2.insert(0, w2[j-1]);
            walign1.insert(0, w1[i-1]);
            walign2.insert(0, '_');
            i -= 1;
            j -= 1;
        }
    }
    // here we are sure that either i or j is 0
    
    for k in 0..i
    {
        walign1.insert(k, w1[k]);
        walign2.insert(k, '_');
    }
    for k in 0..j
    {
        walign1.insert(k, '_');
        walign2.insert(k, w2[k]);
    }
    
    

    (walign1, walign2)
    
}


/// used in q4: same as edit_distance_table but with paragraphs
fn edit_distance_table_parag<F, G, H>(w1: &Vec<Vec<char>>,
                                      w2: &Vec<Vec<char>>,
                                      del: F,
                                      ins: G,
                                      sub: H) -> Vec<Vec<usize>>
where
    F: Fn(&Vec<char>) -> usize,
    G: Fn(&Vec<char>) -> usize,
    H: Fn(&Vec<char>, &Vec<char>) -> usize
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
        table[i][0] = table[i-1][0] + del(&w1[i-1]);
    }

    for j in 1..(n+1)
    {
        table[0][j] = table[0][j-1] + ins(&w2[j-1]);
    }

    for i in 1..(m+1)
    {
        for j in 1..(n+1)
        {
            table[i][j] =
                (table[i][j-1] + ins(&w2[j-1]))
                .min(table[i-1][j] + del(&w1[i-1]))
                .min(table[i-1][j-1] + sub(&w1[i-1], &w2[j-1]));
        }
    }

    
    table
}

/// used in q4: same as best_align but with paragraphs
fn best_align_parag(w1: &Vec<Vec<char>>,
                    w2: &Vec<Vec<char>>) -> (Vec<Vec<char>>, Vec<Vec<char>>)
{
    let del = |par: &Vec<char>| par.len();
    let ins = |par: &Vec<char>| par.len();
    let sub = |a: &Vec<char>, b: &Vec<char>| {
        //        if edit_distance(a, b) < a.len().min(b.len()) {0} else {edit_distance(a, b)}
        edit_distance(a, b)
    };

    let table = edit_distance_table_parag(w1, w2, del, ins, sub);


    let mut i = table.len() - 1;
    let mut j = table[0].len() - 1;

    let mut walign1 = vec![];
    let mut walign2 = vec![];

    
    while i != 0 && j != 0
    {
        let min = table[i][j-1]
            .min(table[i-1][j])
            .min(table[i-1][j-1]);
        
        if table[i][j-1] == min
        {
            walign1.insert(0, vec![]);
            walign2.insert(0, w2[j-1].clone());
            j -= 1;
        }
        else if table[i-1][j] == min
        {
            walign1.insert(0, w1[i-1].clone());
            walign2.insert(0, vec![]);
            i -= 1;
        }
        else if table[i-1][j-1] == min
        {
            walign1.insert(0, w1[i-1].clone());
            walign2.insert(0, w2[j-1].clone());
            i -= 1;
            j -= 1;
        }
        else 
        {
            walign1.insert(0, vec![]);
            walign2.insert(0, w2[j-1].clone());
            walign1.insert(0, w1[i-1].clone());
            walign2.insert(0, vec![]);
            i -= 1;
            j -= 1;
        }

    }

    // here we are sure that either i or j is 0
    
    for k in 0..i
    {
        walign1.insert(k, w1[k].clone());
        walign2.insert(k, vec![]);
    }
    for k in 0..j
    {
        walign1.insert(k, vec![]);
        walign2.insert(k, w2[k].clone());
    }
        

    (walign1, walign2)
    
}


fn test_q3() -> io::Result<()>
{
    println!("///////////////////////////////////////////////////////////////////////////");
    println!("///////////////////////////////////////////////////////////////////////////");
    println!("/// QUESTION 3");
    
    let w1 = read("texte1.txt")?;
    let w2 = read("texte2.txt")?;

    let (wa1, wa2) = best_align(&w1, &w2);
    
    println!("ALIGNEMENT OPTIMAL:");
    println!("{:?}", wa1.iter().collect::<String>());
    println!();
    println!("{:?}", wa2.iter().collect::<String>());
    println!();
    println!();

    Ok(())
}



fn test_q4() -> io::Result<()>
{

    println!("///////////////////////////////////////////////////////////////////////////");
    println!("///////////////////////////////////////////////////////////////////////////");
    println!("/// QUESTION 4");
    
    let w1 = read_parag("t1.txt")?;
    let w2 = read_parag("t2.txt")?;

    let (wa1, wa2) = best_align_parag(&w1, &w2);
    
    for i in 0..wa1.len()
    {
        println!("##################################################");
        println!("{:?}", wa1[i].iter().collect::<String>());
        println!("{:?}", wa2[i].iter().collect::<String>());
    }
    println!();
    println!();
    
    
    Ok(())
}

fn main() -> io::Result<()> {
    test_q3()?;
    test_q4()?;

    Ok(())
}
