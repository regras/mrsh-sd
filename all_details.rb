#!/usr/bin/env ruby
require "./objects.rb"

$types = ['jpg', 'pdf', 'doc', 'ppt', 'html', 'xls', 'text', 'gif']


$scores = [80, 60, 40, 30, 20, 15, 10, 5, 1, 0]


$tp_res = Array.new
$fp_res = Array.new

$sumy_p_file = Hash.new     ##summary per file
$sumy_p_entro = Hash.new    ##summary per entropy


$files = "2.8"


def analyze(dirname, sdhashes_file)
    
    #prepare sdhash file
    sdhash_map = sdhashes_to_hashmap(sdhashes_file)
    
    #iterate through files in 'dirname'
    Dir.chdir(dirname)
    Dir.foreach(".") do |file|
        # something mac specific
        if file.include?($files)
            find_best_sdhash_match(file, sdhash_map)
            print_them(file)
        end
    end
end



#generates true positive statistics
def find_best_sdhash_match(mrsh_net, sdhash_map)
    $scores.each do |s|
        $tp_res[s] = Array.new
    end
    $fp_res = Array.new
    
    #Reset statistics
    $sumy_p_file = Hash.new
    
    #iterate through mrsh results
    file = File.open(mrsh_net, "rb").read
    file.each_line do |line|
        p_array = line.gsub(" \n", "").split(" ")


        #look in sdhash file for a match
        tmp = sdhash_map[get_filename(p_array[0])]
        
        type = get_filename(p_array[0]).split(".")[1]
        
        #if type == "pdf"
        #    next
        #end


        $sumy_p_file['all_files'] = $sumy_p_file['all_files'].to_i + 1     #count all files
        $sumy_p_file['all_packets'] = $sumy_p_file['all_packets'].to_i + p_array[1].to_i


         #store it to results
        if tmp != nil
            $scores.each do |score|
                if tmp.score > score
                    r = RESULT.new
                    r.score = tmp.score
                    r.match = tmp
                    r.mrshnet = p_array
                    $tp_res[score].push(r)
                    break
                end
            end
        else
            $fp_res.push(p_array)
        end
    end
end


def print_them(filename)
        
    puts filename
        
    to = 100
    $scores.each do |score|
        print "sdhash score: > ", score," (",$tp_res[score].length, ")\n"
        $tp_res[score].each do | a |
            print "   ", a.match.name1, " mat ", a.match.name2, "(#{a.score})", a.mrshnet, "\n"
        end
    end
    print "sdhash score = 0\n"
    $fp_res.each do |a|
        print "    ", a[0]," ", a[1]," ", a[2]," ", a[3]," " "\n"
    end
    puts
    
end
    
    

    

def sdhashes_to_hashmap(sdhashes_file)
    #reading hash comaprsion file and build a hashmap
    sdhash_map = Hash.new
    file = File.open(sdhashes_file, "rb").read
    file.each_line do |line|
        #split up the lines to get file names and scores
        lineArr = line.gsub(" \n", "").split("|")

        m = MATCH.new
        m.name1 = get_filename(lineArr[0])
        m.name2 = get_filename(lineArr[1])
        m.score = lineArr[2].to_i
        
           
        #stores best match score for files 
        if sdhash_map[m.name1] == nil || sdhash_map[m.name1].score <= m.score
            sdhash_map[m.name1] = m
        end
        if sdhash_map[m.name2] == nil || sdhash_map[m.name2].score <= m.score
           sdhash_map[m.name2] = m
        end
    end
    return sdhash_map
end


def get_filename(str)
    t = str.split("/")
    return t[t.length-1]
end


def equal_files?(file1, file2)
    f1 = file1.split(".")
    t1 = f1[f1.length - 1]
    f2 = file2.split(".")
    t2 = f2[f2.length - 1]
    return t1==t2
end


#updates counter for a 'file' based on a given package
def update_packet_counter(myfile, packet)
    myfile.total = myfile.total.to_i+1
    if(packet[4].to_i >= $MIN_RUN)
        $total_pos_p = $total_pos_p + 1
        myfile.pos = myfile.pos.to_i + 1
    end
    return myfile
end
    
def splitLine(line)
    tmp = line.gsub(" \n", "").split("/")
    return tmp[tmp.length-1].split(",")
end


analyze(ARGV[0], ARGV[1])



