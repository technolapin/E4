
fn construct_l(wrd: &str) -> Vec<isize>
{
    let word: Vec<_> = wrd.chars().collect();
    let mut l = vec![-1];
    let mut index = -1;

    for j in 1..(word.len()+1)
    {
        while index >= 0 && word[index as usize] != word[j-1]
        {
            index = l[index as usize];
        }

        index += 1;
        l.push(index);
    }
    
    l
}

fn compute_biggest_fronteer(word: &str) -> usize
{
    *construct_l(word).last().unwrap() as usize
}

fn compute_overlap(frag_a: &str, frag_b: &str) -> usize
{
    let concatened = &{
        let mut temp = frag_a.to_string();
        temp.push_str(frag_b);
        temp
    };

    
    let overlap = compute_biggest_fronteer(concatened);

    // la taille de l'overlap ne peut pas être suppérieure à
    // celle des fragments
    let length_max = frag_a.len().min(frag_b.len());

    overlap.min(length_max)

    
}

#[derive(Debug)]
struct OverlapGraph<'a>
{
    nodes: Vec<&'a str>,
    links: Vec<(usize, usize, usize)>
}

impl<'a> OverlapGraph<'a>
{
    fn new() -> Self
    {
        Self
        {
            nodes: vec![],
            links: vec![]
        }
    }
    
    fn with_nodes(frags: Vec<&'a str>) -> Self
    {
        let mut g = Self::new();
        frags.iter()
            .for_each(
                |frag|
                {g.push_node(frag);});
        
        g.gen_links();
        g
    }


    fn push_node(&mut self, frag: &'a str) -> &mut Self
    {
        self.nodes.push(frag);
        self
    }

    // après avoir push les fragments
    fn gen_links(&mut self)
    {
        for i_fra in 0..self.nodes.len()
        {
            for i_frb in 0..self.nodes.len()
            {
                self.links.push((
                    i_fra,
                    i_frb,
                    compute_overlap(self.nodes[i_fra], self.nodes[i_frb])));
            }
        }
        println!();
    }

    fn threshold_links(&mut self, threshold: usize)
    {
        self.links = self.links.iter()
            .filter(
                |&(i, j, n)| *n >= threshold)
            .cloned().collect();
    }

    fn hamiltonian(&self) -> usize
    {
        /// TODO
        self.nodes.enumerate().filter_map(
            |(frag, index)| 
        )
    }
    
    
}


fn main() {
    let l = construct_l("ololo");
    println!("{:?}", l);


    println!("{}", compute_overlap("aaa", "aaa"));
    compute_overlap("aaa", "bab");


    let mut geronte = OverlapGraph::new();
    geronte
        .push_node("CTA")
        .push_node("ACT")
        .push_node("AGT");

    geronte.gen_links();
    println!("{:?}", geronte);

    let mut gilbert = OverlapGraph::with_nodes(
        vec!["CTA", "ACT", "AGT"]
    );
    println!("{:?}", gilbert);

    gilbert.threshold_links(2);
    println!("{:?}", gilbert);
}
