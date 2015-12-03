  
import java.util.Set;
import java.util.HashSet;
import java.util.List;
import java.util.ArrayList;
import java.util.Stack;
import java.util.Deque;
import java.util.ArrayDeque;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileNotFoundException;

class FestivalOfGraphs
{
	private Graph g;
	
	public void init(String graphFile) 
	{
		System.out.println(graphFile);
		// open the file
		BufferedReader br = null;
		
		try
		{
			// open the file called "graph.txt"
			br = new BufferedReader(new FileReader(graphFile));
		
			// read the first line
			String line = br.readLine();	
			
			// convert the first line (a string) to an integer (numberOfVertices)
			Integer n = Integer.parseInt(line);
			
			g = new Graph(n);
		
			for (int fromVertex = 0; fromVertex < n; ++fromVertex)
			{
				line = br.readLine();
				if (line.length() > 0)
				{
					int pos = 0;
					while (line.indexOf("{", pos) > -1)
					{
						String sub = line.substring(line.indexOf("{", pos) + 1, line.indexOf("}", pos + 1));
						Integer toVertex = Integer.parseInt(sub.substring(0, sub.indexOf(",")));
						Integer weightOfEdge = Integer.parseInt(sub.substring(sub.indexOf(",") + 1, sub.length()));
						pos = line.indexOf("}", pos + 1);
						if (!g.hasEdge(fromVertex, toVertex))
							g.addEdge(fromVertex, toVertex, weightOfEdge);
					}	
				}	
			}
		}
		catch (FileNotFoundException ex) {
			// handle FileNotFoundException
			System.out.println("No such file as " + graphFile + " in your directory");
		}
		catch (IOException ex) {
			// handle IOException
			System.out.println("Ran into problems processing " + graphFile);
		}
		finally {
			if (br != null) {
				try {
					br.close();
				}
				catch (IOException ex) {
					// handle IOException
					System.out.println("Ran into unrecoverable problems processing " + graphFile);
				}
			}
		}
		
	}
	
	public List<Integer> DepthFirstList(Integer v)
	{
		List<Integer> vertices = new ArrayList<Integer>();
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		//
		for( Integer i = 0 ; i <= g.getNumVertices(); ++i )
		{
			visited.add(0);
		}
		toExplore.addLast(v);
		visited.set(v,1);
		while( toExplore.size() > 0 )
			{
				Integer w = toExplore.removeFirst();
				vertices.add(w);
			
				for( Integer n : g.getAdjList(w).keySet())
				{
					if( visited.get(n) == 0)
					{
						toExplore.addFirst(n);
						visited.set(n,1);
					}	
				}
			}
		return vertices;
	}
	
	public List<Integer> BreadthFirstList(Integer v) 
	{
		List<Integer> vertices = new ArrayList<Integer>();
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		//
		for( Integer i = 0 ; i <= g.getNumVertices(); ++i )
		{
			visited.add(0);
		}
		toExplore.addLast(v);
		visited.set(v,1);
		while( toExplore.size() > 0 )
			{
				Integer w = toExplore.removeFirst();
				vertices.add(w);
			
				for( Integer n : g.getAdjList(w).keySet())
				{
					if( visited.get(n) == 0)
					{
						toExplore.addLast(n);
						visited.set(n,1);
					}	
				}
			}
		return vertices;
	}

	
	public Graph DepthFirstSpanningTree(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		//
		for( Integer i = 0 ; i <= g.getNumVertices(); ++i )
		{
			visited.add(0);
		}
		toExplore.addLast(v);
		visited.set(v,1);
		while( toExplore.size() > 0 )
			{
				Integer w = toExplore.removeFirst();
				for( Integer n : g.getAdjList(w).keySet())
				{
					if( visited.get(n) == 0)
					{
						t.addEdge(w,n,1);
						toExplore.addFirst(n);
						visited.set(n,1);
					}	
				}
			}
		return t;
	}
	
	
	public Graph BreadthFirstSpanningTree(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		//
		for( Integer i = 0 ; i <= g.getNumVertices(); ++i )
		{
			visited.add(0);
		}
		toExplore.addLast(v);
		visited.set(v,1);
		while( toExplore.size() > 0 )
			{
				Integer w = toExplore.removeFirst();
				for( Integer n : g.getAdjList(w).keySet())
				{
					if( visited.get(n) == 0)
					{
						t.addEdge(w,n,1);
						toExplore.addLast(n);
						visited.set(n,1);
					}	
				}
			}
		return t;
	}

	List<String> DijkstrasShortestPath(Integer t)
	{
		List<Integer> initialized = new ArrayList<Integer>();
		List<Integer> pathWeights = new ArrayList<Integer>();
		List<String> prettyWeights = new ArrayList<String>();
		
		Set<Integer> vertexSet = new HashSet<Integer>();
		
		return prettyWeights;
	}
	
	public Graph PrimsAlgorithm(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		return t;
	}
	
	
}

